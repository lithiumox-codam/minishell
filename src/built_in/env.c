/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 23:12:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/21 18:15:44 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(t_vector *env_vec)
{
	size_t	i;
	size_t	**arr;

	i = 0;
	arr = return_sorted_arr(env_vec);
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		printf("%s=%s\n", ((t_env *)vec_get(env_vec, *arr[i]))->key,
			((t_env *)vec_get(env_vec, *arr[i]))->value);
		i++;
	}
	ft_free_size_t(arr, env_vec->length);
	exit(0);
}
