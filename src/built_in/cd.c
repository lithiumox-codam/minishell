/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:29:00 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/17 01:07:00 by mdekker/jde   ########   odam.nl         */
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
 * @brief Prints the error message for cd
 * @param path The path that caused the error
 * @return void
 */
static void	print_err_cd(char *path)
{
	printf("cd: %s: %s\n", strerror(errno), path);
	g_signal.exit_status = 1;
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
 * @brief Changes the current working directory to the one specified in the
 * argument or to the HOME directory if no argument is given
 *
 * @param group The group struct with the args
 * @param env The environment
 * @return void
 */
void	ft_cd(t_group *group, t_vector *env)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exit_mini("ft_cd", 1);
	if (!group->args[1])
		path = safe_env_get(env, "HOME");
	else if (ft_strcmp(group->args[1], "-") == 0)
		path = safe_env_get(env, "OLDPWD");
	else
		path = group->args[1];
	if (!path)
	{
		printf("cd: HOME not set\n");
		g_signal.exit_status = 1;
		return ;
	}
	if (chdir(path) == -1)
		print_err_cd(path);
	else
		update_env(env, "OLDPWD", oldpwd);
	free(oldpwd);
}
