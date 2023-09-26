/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/26 23:44:33 by mdekker/jde   ########   odam.nl         */
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
	t_found	*current_found;
	t_found	*next_found;
	t_token	*current_token;
	t_token	*next_token;
	size_t	i;

	i = 0;
	while (i < found->length - 1)
	{
		current_found = (t_found *)vec_get(found, i);
		next_found = (t_found *)vec_get(found, i + 1);
		current_token = (t_token *)current_found->item;
		next_token = (t_token *)next_found->item;
		if (next_found->index - current_found->index == 1)
			if (current_token->type == next_token->type)
				return (set_err(SYNTAX, type_symbol(current_token->type), data),
						false);
		i++;
	}
	return (true);
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
static bool	check_heredoc(t_vector *found, t_shell *data)
{
	t_found	*current_found;
	t_token	*current_token;
	t_token	*next_token;
	size_t	i;
	size_t	offset;

	i = 0;
	offset = 0;
	while (i < found->length)
	{
		current_found = (t_found *)vec_get(found, i);
		current_token = (t_token *)(current_found->item - (offset
					* sizeof(t_token)));
		if (current_token->type == HEREDOC)
		{
			/* TODO: This does not properly check if the heredoc is at the end.. maybe just look in the data vec? */
			if (i == found->length - (offset + 1) && i == data->token_vec.length
				- 1)
				return (set_err(SYNTAX, type_symbol(current_token->type), data),
						false);
			next_token = (t_token *)vec_get(&data->token_vec,
											current_found->index + 1 - offset);
			if (next_token->type != STRING)
				return (set_err(SYNTAX, type_symbol(current_token->type), data),
						false);
			else
			{
				if (!combine_heredoc(&data->token_vec, current_found->index
						- offset))
					return (false);
				offset++;
			}
		}
		i++;
	}
	return (true);
}

void	print_t_found(void *item, size_t index)
{
	t_found	*found;

	found = (t_found *)item;
	if (index == 0)
		printf("\033[1;33m├── Found Vector 👇\n");
	else
		printf("\033[1;31m●\n");
	printf("\033[1;33m│\n");
	printf("├── Found %zu:\n", index);
	printf("│   ├── Item: %p\n", found->item);
	printf("│   ├── Index: %zu\n", found->index);
	printf("│   └── Adress: %p\n", found);
	printf("\033[1;33m│\n");
	printf("\033[0m");
}

bool	check_tokens(t_shell *data)
{
	t_vector	*found;
	t_found		*found_item;
	t_token		*token;
	size_t		i;

	i = 0;
	found = vec_find(&data->token_vec, filter_operators);
	if (found == NULL)
		return (set_err(MALLOC, "vector found returned NULL", data), true);
	print_vector(found, print_t_found);
	found_item = (t_found *)vec_get(found, i);
	token = (t_token *)found_item->item;
	if (found_item->index == 0 && type_compare(5, token->type, PIPE, OR, AND,
			I_REDIRECT, O_REDIRECT))
		return (set_err(SYNTAX, type_symbol(token->type), data),
				vec_free(found),
				free(found),
				false);
	if (!check_double_ops(found, data))
		return (vec_free(found), free(found), false);
	if (!check_heredoc(found, data))
		return (vec_free(found), free(found), false);
	vec_free(found);
	free(found);
	return (true);
}
