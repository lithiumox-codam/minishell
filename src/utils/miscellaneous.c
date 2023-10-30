/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:53:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/30 18:33:35 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief	checks if token->type is a redirect
 * @note	redirects include O_REDIRECT I_REDIRECT A_REDIRECT HEREDOC
 * @return	true if its a redirect type
 * 			false if not
 */
bool	is_redirect(t_token *token)
{
	if (token->type == O_REDIRECT || token->type == I_REDIRECT
		|| token->type == A_REDIRECT || token->type == HEREDOC ||
		token->type == HDOC_LITERAL)
	{
		return (true);
	}
	return (false);
}
