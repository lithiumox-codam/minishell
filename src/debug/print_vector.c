/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 13:51:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 13:52:28 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints a t_token vector in a pretty way
 *
 * @param tokens t_vector of t_token structs
 */
void print_token_vector(t_vector *tokens)
{
	t_token *token;
	size_t i;

	i = 0;
	while (i < tokens->lenght)
	{
		token = (t_token *)ft_vec_get(tokens, i);
		if (token != NULL)
		{
			printf("\033[1;32m●\n");
			printf("\033[1;34m│\n");
			printf("├── Token %zu:\n", i++);
			printf("│   ├── Value: %s\n", token->value);
			printf("│   ├── Type: %i\n", token->type);
			printf("│   └── Adress: %p\n", token);
			printf("\033[1;34m│\n");
			printf("\033[0m");
		}
	}
}
