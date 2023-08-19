/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:53:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/19 16:53:41 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*rm_quotes(t_token *token)
{
	if (token->type == STRING)
		return (token->value);
	if (token->type == SINGLE_QUOTE)
		return (ft_strtrim(token->value, "\'"));
	if (token->type == DOUBLE_QUOTE)
		return (ft_strtrim(token->value, "\""));
}
