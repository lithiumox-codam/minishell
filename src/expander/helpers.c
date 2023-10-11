/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 12:54:14 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/11 15:35:41 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Returns the value in the environment for the given key
 *
 * @param key The key to search for
 * @return char* The value in the environment or NULL if not found
 */
char	*find_in_env(char *key, t_shell *data)
{
	size_t	i;

	i = 0;
	while (i < &data->env.length)
	{
		if (ft_strcmp(((t_env *)vec_get(&data->env, i))->key, key + 1) == 0)
			return (((t_env *)vec_get(&data->env, i))->value);
		i++;
	}
	return (NULL);
}
