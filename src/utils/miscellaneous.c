/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miscellaneous.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:53:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/08 16:26:58 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*rm_quotes(t_token *token)
{
	char	*temp;

	if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
	{
		if (ft_strlen(token->value) == 2)
		{
			free(token->value);
			token->value = ft_strdup("");
		}
	}
	if (token->type == SINGLE_QUOTE)
	{
		temp = ft_strtrim(token->value, "\'");
		free(token->value);
		token->value = temp;
	}
	if (token->type == DOUBLE_QUOTE)
	{
		temp = ft_strtrim(token->value, "\"");
		free(token->value);
		token->value = temp;
	}
	token->type = STRING;
	return (token);
}

/**
 * @brief	checks if token->type is a redirect
 * @note	redirects include O_REDIRECT I_REDIRECT A_REDIRECT HEREDOC
 * @return	true if its a redirect type
 * 			false if not
 */
bool	is_redirect(t_token *token)
{
	if (token->type == O_REDIRECT || token->type == I_REDIRECT
		|| token->type == A_REDIRECT || token->type == HEREDOC)
	{
		return (true);
	}
	return (false);
}

/**
 * @brief	checks if token->type is a string, single-or double_quote
 * @note	includes STRING SINGLE_QUOTE DOUBLE_QUOTE
 * @return	true is its a string type
 * 			false if not
 */
bool	is_string_type(t_token *token)
{
	if (token->type == STRING || token->type == SINGLE_QUOTE
		|| token->type == DOUBLE_QUOTE)
	{
		return (true);
	}
	return (false);
}
