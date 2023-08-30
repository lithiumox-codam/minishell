/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/31 00:43:21 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief loop cause it didnt fit in verify_token xd
 */
static void	loop(t_vector *token_vec)
{
	int		i;
	t_token	*token;
	t_token	*next;

	i = 0;
	while (i < token_vec->length)
	{
		token = vec_get(&token_vec, i);
		if (token->type == O_REDIRECT || token->type == I_REDIRECT
			|| token->type == A_REDIRECT || token->type == HEREDOC)
		{
			check_redirect(token_vec, i);
			i++;
		}
		else if (i + 1 < token_vec->length)
		{
			next = vec_get(&token_vec, i + 1);
			if (token->type == PIPE && next->type == PIPE)
				err(SYNTAX, next->value, NULL, NULL);
		}
		i++;
	}
}

/**
 * @brief checks if redirect is followed by STRING/D_QUOTE/S_QUOTE
 */
static void	check_redirect(t_vector *token_vec, int i)
{
	t_token	*token;
	t_token	*next;

	token = vec_get(&token_vec, i);
	if (i + 1 >= token_vec->length)
		err(SYNTAX, "`newline'", NULL, NULL);
	next = vec_get(&token_vec, i + 1);
	if (next->type != STRING || next->type != DOUBLE_QUOTE
		|| next->type != SINGLE_QUOTE)
		err(SYNTAX, next->value, NULL, NULL);
}

/**
 * @brief verifies that the input doesnt start with a pipe,
	checks for double pipes
 * @brief checks if redirects/heredocs are followe by a string/quoted string
 * @param	vec the vector of t_tokens
 */
void	verify_token(t_vector *token_vec)
{
	int		i;
	t_token	*token;

	i = 0;
	token = vec_get(&token_vec, i);
	if (token->type == PIPE)
		err(SYNTAX, token->value, NULL, NULL);
	loop(token_vec);
	if (token_vec->length > 1)
	{
		i = token_vec->length - 1;
		token = vec_get(&token_vec, i);
		if (token->type == PIPE)
			err(SYNTAX_MINI, token->value, NULL, NULL);
	}
}
