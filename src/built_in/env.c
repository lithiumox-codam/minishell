/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 23:12:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 22:55:19 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief The env command built-in
 * @details Prints the enviroment variables
 *
 * @warning This function also sorts the enviroment variables alphabetically
 * which is technically not part of the env command but if you want me to
 * remove it, I can. I just thought it would be nice to have it sorted.
 *
 * @param env_vec The enviroment vector
 */
void	ft_env(t_vector *env_vec)
{
	size_t	i;
	size_t	**arr;
	char	*value;

	i = 0;
	arr = return_sorted_arr(env_vec);
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		value = ((t_env *)vec_get(env_vec, *arr[i]))->value;
		if (value)
			printf("%s=%s\n", ((t_env *)vec_get(env_vec, *arr[i]))->key, value);
		i++;
	}
	ft_free_size_t(arr, env_vec->length);
	exit(0);
}
