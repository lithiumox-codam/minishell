/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 21:12:42 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/14 20:47:54 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_found(t_vector *found)
{
	vec_free(found);
	free(found);
}

/**
 * @brief Checks if the tokens contain OR and AND operators because they
 * are bonus and were not implementing that.
 * @param found The vector of found tokens
 *
 * @return true The tokens do not contain OR and AND operators
 * @return false The tokens do contain OR and AND operators
 */
bool	out_of_scope(t_vector *found, t_shell *data)
{
	size_t i;
	t_found *current_found;
	t_token *current_token;
	i = 0;
	while (i < found->length)
	{
		current_found = (t_found *)vec_get(found, i);
		current_token = (t_token *)current_found->item;
		if (current_token->type == AND || current_token->type == OR)
			return (set_err(OUT_OF_SCOPE, type_symbol(current_token->type),
					data), false);
		i++;
	}
	return (true);
}