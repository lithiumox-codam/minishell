/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 18:52:54 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/20 18:09:17 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints the entire environment with 'declare -x' in front of it
 *
 * @param env The environment to print
 * @param arg_2 The second argument of the command if there is one
 * @return void
 */
void	print_env_dec(t_vector *env, char *arg_2)
{
	size_t	i;

	i = 0;
	if (arg_2)
		return ;
	while (i < env->length)
	{
		printf("declare -x %s=%s\n", ((t_env *)vec_get(env, i))->key,
			((t_env *)vec_get(env, i))->value);
		i++;
	}
}
/**
 * @brief Updates the value of an environment variable when it already exists or
 * creates a new one if it doesn't (used in cd to update PWD and OLDPWD)
 * @param env The environment vector
 * @param key The key to compare to
 * @param value The value to update or create
 * @return void
 */
void	update_or_create_env(t_vector *env, char *key, char *value)
{
	t_env	*env_var;

	env_var = vec_find_f(env, compare_env_key, key);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
	}
	else
	{
		if (!vec_push(env, create_env(key, ft_strdup(value))))
			exit_mini("update_or_create_env", 1);
	}
}
