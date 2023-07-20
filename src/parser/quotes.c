/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 11:37:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 16:46:11 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_encased_dq(char *str)
{
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (true);
	return (false);
}

bool	is_encased_sq(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (true);
	return (false);
}

bool	is_encased_parentheses(char *str)
{
	if (str[0] == '(' && str[ft_strlen(str) - 1] == ')')
		return (true);
	return (false);
}
