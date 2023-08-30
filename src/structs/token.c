/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 22:36:40 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/30 21:44:06 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Create a token object
 *
 * @param value A string containing the value of the token
 * @param type The type of the token
 * @return t_token* The created token, NULL if malloc error
 */
t_token	*create_token(char *value, t_types type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

/**
 * @brief Prints a token struct
 *
 * @param data The token struct
 * @param i The index of the token
 */
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
	printf("│   ├── Type: %s\n", print_type(token->type));
	printf("│   └── Adress: %p\n", token);
	printf("\033[1;34m│\n");
	printf("\033[0m");
}

/**
 * @brief Clears a token struct
 *
 * @param data The token struct
 */
void	clear_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	free(token->value);
}

t_token	*dup_token(t_token *input)
{
	t_token	*dup;

	dup = malloc(sizeof(t_token));
	if (!dup)
		return (NULL);
	if (!input->value)
		dup->value = NULL;
	else
	{
		dup->value = ft_strdup(input->value);
		if (!dup->value)
			return (free(dup), NULL);
	}
	dup->type = input->type;
	return (dup);
}
