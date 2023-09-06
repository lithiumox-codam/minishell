/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 19:44:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 17:07:42 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_built_in(char *str)
{
	if (ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "cd") == 0)
		return (true);
}

char	**combine_env(t_vector *env_vec)
{
}
