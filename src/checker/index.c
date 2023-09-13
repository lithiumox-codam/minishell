/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/13 18:07:01 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	filter_operators(void *item)
{
	t_token	*token;

	token = (t_token *)item;
	if (type_compare(5, token->type, PIPE, HEREDOC, O_REDIRECT, I_REDIRECT, AND,
			OR))
		return (true);
	return (false);
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
		if (current_token->type == next_token->type)
			return (set_err(SYNTAX, type_symbol(current_token->type), data),
					false);
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
		return (set_err(SYNTAX, "vector found returned NULL", data), true);
	printf("Found: %p\n", found);
	print_vector(found, print_t_found);
	found_item = (t_found *)vec_get(found, i);
	token = (t_token *)found_item->item;
	if (found_item->index == 0 && type_compare(1, token->type, PIPE))
		return (set_err(SYNTAX, type_symbol(token->type), data),
				vec_free(found),
				free(found),
				false);
	else if (found && !check_double_ops(found, data))
	{
		vec_free(found);
		free(found);
		return (false);
	}
	if (found)
	{
		vec_free(found);
		free(found);
	}
	return (true);
}
