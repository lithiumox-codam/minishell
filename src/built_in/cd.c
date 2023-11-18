/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:29:00 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/18 23:49:02 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

/**
 * @brief Updates the value of an environment variable when it already exists
 * @param env_var The env struct
 * @param key The key to compare to
 * @return void
 */
static void	update_env(t_vector *env, char *key, char *value)
{
	t_env	*env_var;

	env_var = vec_find_f(env, compare_env_key, key);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
	}
}

/**
 * @brief Helper function for vec_find_f to safely get an environment variable
 * @param *env The environment vector
 * @param *key The key to compare to
 * @return char* The value of the environment variable or NULL
 */
static char	*safe_env_get(t_vector *env, char *key)
{
	t_env	*env_var;

	env_var = vec_find_f(env, compare_env_key, key);
	if (env_var)
		return (env_var->value);
	return (NULL);
}

/**
 * @brief Prints the error message for cd
 * @param path The path that caused the error
 * @return void
 *
 * TODO: Does not work properly in all cases
 */
static bool	error_check(t_shell *data, t_group *group)
{
	if (group->args[2])
	{
		printf("cd: too many arguments\n");
		data->error_type = CATCH_ALL;
		return (false);
	}
	if (!ft_strcmp(group->args[1], "-"))
	{
		printf("%s\n", safe_env_get(&data->env, "OLDPWD"));
		data->error_type = CATCH_ALL;
		return (false);
	}
	return (true);
}

static char	*get_path(t_group *group, t_shell *data)
{
	char	*path;

	if (!group->args[1])
		path = safe_env_get(&data->env, "HOME");
	else if (ft_strcmp(group->args[1], "~") == 0)
		path = safe_env_get(&data->env, "HOME");
	else if (ft_strncmp(group->args[1], "~/", 2) == 0)
		path = ft_strjoin(safe_env_get(&data->env, "HOME"), group->args[1] + 1);
	else
		path = group->args[1];
	return (path);
}

/**
 * @brief Changes the current working directory to the one specified in the
 * argument or to the HOME directory if no argument is given
 *
 * @param group The group struct with the args
 * @param env The environment
 * @return void
 */
void	ft_cd(t_group *group, t_shell *data)
{
	char	*path;
	char	*oldpwd;

	if (!error_check(data, group))
		return ;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exit_mini("ft_cd", 1);
	path = get_path(group, data);
	if (!path)
	{
		printf("cd: HOME not set\n");
		data->error_type = CATCH_ALL;
		return ;
	}
	if (chdir(path) == -1)
		printf("cd: %s: %s\n", strerror(errno), path);
	else
		update_env(&data->env, "OLDPWD", oldpwd);
	free(oldpwd);
}
