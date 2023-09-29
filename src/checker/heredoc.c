/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 22:15:51 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/29 15:06:13 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Combines the given and next token into one token
 *
 * @param vec The vector to combine in of tokens
 * @param i The index of the first token
 * @return true If the tokens were combined
 * @return false If the tokens could not be combined
 */
bool	combine_tokens(t_vector *vec, size_t i, t_types type)
{
	t_token	*token;

	token = vec_get(vec, i + 1);
	if (!token)
		return (false);
	token->type = type;
	if (!vec_remove(vec, i))
		return (false);
	return (true);
}
