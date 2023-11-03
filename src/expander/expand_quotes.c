/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 17:11:52 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/02 17:12:25 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	expand_sq(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	(*i)++;
	while (token->value[(*i)] != '\'')
	{
		if (!char_vec_push(vec, token->value[(*i)]))
			return (set_err(MALLOC, "expand_sq", data));
		(*i)++;
	}
	(*i)++;
	if (token->type == HEREDOC)
		token->type = HDOC_LITERAL;
	return (true);
}

bool	expand_dq(t_token *token, size_t *i, t_vector *vec, t_shell *data)
{
	(*i)++;
	while (token->value[(*i)] != '\"')
	{
		if (token->value[(*i)] == '$')
		{
			if (!expand_env(token->value, i, vec, data))
				return (false);
		}
		else
		{
			if (!char_vec_push(vec, token->value[(*i)]))
				return (set_err(MALLOC, "expand_dq", data));
			(*i)++;
		}
	}
	(*i)++;
	if (token->type == HEREDOC)
		token->type = HDOC_LITERAL;
	return (true);
}
