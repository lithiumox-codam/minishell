/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:29:02 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 16:29:52 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	contains_env_var(char *str)
{
	if (ft_strchr(str, '$'))
		return (true);
	return (false);
}

bool	is_and(char *str)
{
	if (ft_strcmp(str, "&&") == 0)
		return (true);
	return (false);
}

bool	is_or(char *str)
{
	if (ft_strcmp(str, "||") == 0)
		return (true);
	return (false);
}
