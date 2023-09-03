/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/03 20:23:18 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief loop cause it didnt fit in verify_token xd
 */
static void	loop(t_shell *data)
{
	int		i;
	t_token	*token;
	t_token	*next;

	i = 0;
	while (i < (&data->token_vec)->length)
	{
		token = vec_get(&data->token_vec, i);
		if (is_redirect(token))
		{
			check_redirect(&data->token_vec, i);
			i++;
		}
		else if (i + 1 < (&data->token_vec)->length)
		{
			next = vec_get(&data->token_vec, i + 1);
			if (token->type == next->type)
				err(SYNTAX, next->value, data, false);
		}
		i++;
	}
}

/**
 * @brief checks if redirect is followed by STRING/D_QUOTE/S_QUOTE
 */
static void	check_redirect(t_shell *data, int i)
{
	t_token	*next;

	if (i + 1 >= (&data->token_vec)->length)
		err(SYNTAX, "newline", data, false);
	next = vec_get(&data->token_vec, i + 1);
	if (!is_string_type(next))
		err(SYNTAX, next->value, data, false);
}

/**
 * @brief verifies that the input doesnt start with a pipe,
	checks for double pipes
 * @brief checks if redirects/heredocs are followe by a string/quoted string
 * @param	vec the vector of t_token_vec
 */
void	verify_token_vec(t_shell *data)
{
	int		i;
	t_token	*token;

	i = 0;
	token = vec_get(&data->token_vec, i);
	if (token->type == PIPE)
		err(SYNTAX, token->value, data, false);
	loop(data);
	if ((&data->token_vec)->length > 1)
	{
		i = (&data->token_vec)->length - 1;
		token = vec_get(&data->token_vec, i);
		if (token->type == PIPE)
			err(SYNTAX_MINI, token->value, data, false);
	}
}
