/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 23:12:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/16 23:13:13 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_vector *env_vec)
{
	size_t i;

	i = 0;
	while (i < env_vec->length)
	{
		printf("%s=%s\n", ((t_env *)vec_get(env_vec, i))->key,
			((t_env *)vec_get(env_vec, i))->value);
		i++;
	}
	exit(0);
}