/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/17 21:05:59 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_vec(t_vector *tokens)
{
	t_token	*token;

	printf("tokens->used: %zu\n", tokens->used);
	for (size_t i = 0; i < tokens->used; i++)
	{
		token = (t_token *)ft_vec_get(tokens, i);
		if (DEBUG)
			printf("[%zu]: %s (%i)\n", i, token->value, token->type);
	}
}

static void	clear_structs_vec(t_vector *tokens)
{
	t_token	*token;

	while (tokens->used > 0)
	{
		token = (t_token *)ft_vec_pop(tokens);
		printf("token->value: %p\n", token->value);
		free(token);
	}
}

static void	tokenize(char *input, t_vector tokens)
{
	char	**tmp;
	t_token	*token;
	size_t	i;

	i = 0;
	tmp = ft_split(input, ' ');
	while (tmp[i])
	{
		token = malloc(sizeof(t_token));
		token->type = DOUBLE_QUOTE;
		token->value = tmp[i];
		printf("token->value: %s\n", token->value);
		ft_vec_push(&tokens, (void *)token);
		free(*tmp);
		i++;
	}
	print_vec(&tokens);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_vector	tokens;

	(void)ac;
	(void)av;
	(void)env;
	tokens = (t_vector){NULL, 0, 0, 0};
	while (1)
	{
		if (tokens.data == NULL)
			ft_vec_init(&tokens, 5, sizeof(t_token));
		input = readline("\n\033[1;32mminishell$ \033[0m");
		if (!input)
			break ;
		add_history(input);
		if (mini_strcmp(input, "exit"))
			return (free(input), 0);
		else if (!check_quotes_parantheses(input))
			printf("minishell: syntax error: unfinished quote or parantheses\n");
		else
			tokenize(input, tokens);
		free(input);
		clear_structs_vec(&tokens);
		printf("tokens->used: %zu\n", tokens.used);
	}
	return (0);
}
