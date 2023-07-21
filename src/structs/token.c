/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 22:36:40 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 03:54:56 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

void	print_token(void *data, size_t i)
{
	t_token	*token;

	token = (t_token *)data;
	if (i == 0)
		printf("\033[1;34m├── Token Vector 👇\n");
	else
		printf("\033[1;32m●\n");
	printf("\033[1;34m│\n");
	printf("├── Token %zu:\n", i);
	printf("│   ├── Value: %s\n", token->value);
	printf("│   ├── Type: %i\n", token->type);
	printf("│   └── Adress: %p\n", token);
	printf("\033[1;34m│\n");
	printf("\033[0m");
}

void	clear_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	free(token->value);
}
