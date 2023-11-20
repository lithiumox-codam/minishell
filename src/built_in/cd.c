/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:29:00 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/20 20:52:14 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Updates the value of an environment variable when it already exists
 * @param env_var The env struct
 * @param key The key to compare to
 * @return void
 */
static void	update_env(t_shell *data, char *oldpwd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	update_or_create_env(&data->env, "OLDPWD", oldpwd);
	update_or_create_env(&data->env, "PWD", buff);
	free(buff);
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
	char	*path;

	if (group->args[2])
	{
		printf("cd: too many arguments\n");
		data->error_type = CATCH_ALL;
		return (false);
	}
	if (!ft_strcmp(group->args[1], "-"))
	{
		path = safe_env_get(&data->env, "OLDPWD");
		if (!path)
		{
			printf("cd: OLDPWD not set\n");
			data->error_type = CATCH_ALL;
			return (false);
		}
		printf("%s\n", path);
		data->error_type = CATCH_ALL;
		return (false);
	}
	return (true);
}

/**
 * @brief Gets the path to change to
 *
 * @param group The group struct with the args
 * @param data The shell struct
 * @return char* The path to change to
 */
static char	*get_path(t_group *group, t_shell *data)
{
	char	*path;

	if (!group->args[1] || !ft_strcmp(group->args[1], "~"))
	{
		path = safe_env_get(&data->env, "HOME");
		if (!path)
		{
			printf("cd: HOME not set\n");
			data->error_type = CATCH_ALL;
			return (NULL);
		}
	}
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
	{
		printf("cd: error retrieving current directory: %s\n", strerror(errno));
		data->error_type = CATCH_ALL;
		return ;
	}
	path = get_path(group, data);
	if (!path)
		return ;
	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		data->error_type = CATCH_ALL;
	}
	else
		update_env(data, oldpwd);
	data->error_type = NO_ERROR;
	free(oldpwd);
	// This is a hacky for a memleak in get_path
	if (strncmp(path, group->args[1], 2) != 0)
		free(path);
}
