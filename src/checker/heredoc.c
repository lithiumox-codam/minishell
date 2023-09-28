/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/13 22:15:51 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/28 12:35:58 by mdekker/jde   ########   odam.nl         */
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
bool	combine_heredoc(t_vector *vec, size_t i)
{
	t_token	*token;

	token = vec_get(vec, i + 1);
	token->type = HEREDOC;
	if (!token)
		return (false);
	if (!vec_remove(vec, i))
		return (false);
	return (true);
}
