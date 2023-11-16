/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 17:29:00 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/16 23:11:28 by mdekker/jde   ########   odam.nl         */
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
 * @brief Changes the current working directory to the one specified in the
 * argument or to the HOME directory if no argument is given
 *
 * @param group The group struct with the args
 * @param env The environment
 * @return void
 *
 * !TODO: '-' not working afaik but not know if I need it..
 */
void	ft_cd(t_group *group, t_vector *env)
{
	char	*path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		exit_mini("ft_cd", 1);
	if (!group->args[1])
		path = vec_find_f(env, compare_env_key, "HOME");
	else if (ft_strcmp(group->args[1], "-") == 0)
		path = vec_find_f(env, compare_env_key, "OLDPWD");
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
