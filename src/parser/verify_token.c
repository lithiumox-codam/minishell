/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/09 12:42:49 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	filter_operators(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	return (t->type == PIPE || t->type == AND || t->type == OR
		|| t->type == I_REDIRECT || t->type == O_REDIRECT
		|| t->type == A_REDIRECT || t->type == HEREDOC);
}

static bool	check_double_ops(t_found **found)
{
	t_token	*token;

	token = (*found)->item;
	if (token->type == ((t_token *)(((t_found *)(*(found + 1)))->item))->type)
	{
		if (token->type == PIPE)
			set_err(SYNTAX, "syntax error near unexpected token `||'", NULL);
		else if (token->type == AND)
			set_err(SYNTAX, "syntax error near unexpected token `&&'", NULL);
		else if (token->type == O_REDIRECT)
			set_err(SYNTAX, "syntax error near unexpected token `>>'", NULL);
		else if (token->type == I_REDIRECT)
			set_err(SYNTAX, "syntax error near unexpected token `<<'", NULL);
		else if (token->type == A_REDIRECT)
			set_err(SYNTAX, "syntax error near unexpected token `<<'", NULL);
		else if (token->type == HEREDOC)
			set_err(SYNTAX, "syntax error near unexpected token `<<'", NULL);
		return (false);
	}
	return (true);
}

bool	check_tokens(t_shell *data)
{
	t_found	**found;
	t_token	*token;

	found = vec_find(&data->token_vec, filter_operators);
	if (found == NULL)
	{
		set_err(SYNTAX, "syntax error near unexpected token", data);
		return (false);
	}
	while (*found != NULL)
	{
		token = (*found)->item;
		if (token->type == PIPE || token->type == AND || token->type == OR)
		{
			if (!check_double_ops(found))
				return (false);
		}
		found++;
	}
	while (*found != NULL)
	{
		free(*found);
		found++;
	}
	return (true);
}
