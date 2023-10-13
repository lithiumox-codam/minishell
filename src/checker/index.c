/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/11 16:09:31 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	filter_operators(void *item)
{
	t_token	*token;

	token = (t_token *)item;
	return (type_compare(6, token->type, PIPE, HEREDOC, O_REDIRECT, I_REDIRECT,
			A_REDIRECT, AND, OR));
}

static bool	check_double_ops(t_vector *found, t_shell *data)
{
	t_found	*c_found;
	t_found	*next_found;
	t_token	*c_token;
	t_token	*n_token;
	size_t	i;

	i = 0;
	while (i < found->length - 1)
	{
		c_found = (t_found *)vec_get(found, i);
		next_found = (t_found *)vec_get(found, i + 1);
		c_token = (t_token *)c_found->item;
		n_token = (t_token *)next_found->item;
		if (next_found->index - c_found->index == 1)
			if (c_token->type == n_token->type)
				return (set_err(SYNTAX, type_symbol(c_token->type), data),
						false);
		i++;
	}
	return (true);
}

/**
 * @brief This function decrements the index of a found item
 *
 * @warning This function causes the vector to be completely reindexed
 * and thus will cause the index of the found item to be incorrect.
 * So dont use the vector in question after this function has been called!
 *
 * @param found The found item to decrement
 */
static void	decrement_index(void *found)
{
	t_found	*c_found;

	c_found = (t_found *)found;
	if (c_found->index != 0)
	{
		c_found->item -= sizeof(t_token);
		c_found->index--;
	}
}

/**
 * @brief A function that checks if every heredoc has a string after it
 * if so it combines the two tokens into one for the execution
 *
 * @param found The found vector
 * @param data The shell struct
 * @return true When every heredoc has a string after it
 * @return false When a heredoc does not have a string after it
 */
static bool	check_ops(t_vector *found, t_shell *data)
{
	t_found	*c_found;
	t_token	*c_token;
	t_token	*n_token;
	size_t	i;

	i = 0;
	while (i < found->length)
	{
		c_found = (t_found *)vec_get(found, i);
		c_token = (t_token *)(c_found->item);
		if (c_token->type >= 11 && c_token->type <= 14)
		{
			n_token = (t_token *)vec_get(&data->token_vec, c_found->index + 1);
			if (!n_token || n_token->type != STRING)
				return (set_err(SYNTAX, type_symbol(c_token->type), data),
						false);
			else if (!combine_tokens(&data->token_vec, c_found->index,
						c_token->type))
				return (false);
			else
				vec_apply(found, decrement_index);
		}
		i++;
	}
	return (true);
}

static bool	check_bounds(t_vector *found, t_shell *data)
{
	t_found	*first;
	t_token	*last_t;
	t_found	*last;
	t_token	*first_t;

	if (found->length == 0)
		return (true);
	first = (t_found *)vec_get(found, 0);
	last = (t_found *)vec_get(found, found->length - 1);
	first_t = (t_token *)first->item;
	last_t = (t_token *)last->item;
	if (first->index == 0 && (first_t->type >= 5 && first_t->type <= 7))
		return (set_err(SYNTAX, type_symbol(first_t->type), data), false);
	if (last->index == data->token_vec.length - 1)
		return (set_err(SYNTAX, type_symbol(last_t->type), data), false);
	return (true);
}

bool	check_tokens(t_shell *data)
{
	t_vector	*found;

	found = vec_find(&data->token_vec, filter_operators);
	if (found == NULL)
		return (set_err(MALLOC, "vector found returned NULL", data), true);
	if (!check_bounds(found, data))
		return (free_found(found), false);
	if (!check_double_ops(found, data))
		return (free_found(found), false);
	if (!check_ops(found, data))
		return (free_found(found), false);
	free_found(found);
	return (true);
}
