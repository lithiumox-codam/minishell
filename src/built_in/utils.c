/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 18:52:54 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/17 15:26:12 by mdekker       ########   odam.nl         */
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
