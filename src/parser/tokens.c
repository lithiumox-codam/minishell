/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 14:50:46 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 16:28:50 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (true);
	return (false);
}

bool	is_r_redirect(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (true);
	return (false);
}

bool	is_l_redirect(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (true);
	return (false);
}

bool	is_r_hd(char *str)
{
	if (ft_strcmp(str, ">>") == 0)
		return (true);
	return (false);
}

bool	is_l_hd(char *str)
{
	if (ft_strcmp(str, "<<") == 0)
		return (true);
	return (false);
}
