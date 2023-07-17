/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/17 22:10:29 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pretty_print_vector(t_vector *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->size)
	{
		token = (t_token *)ft_vec_get(tokens, i);
		if (token != NULL)
		{
			printf("Token %zu:\n", i);
			printf("  Value: %s\n", token->value);
			printf("  Type: %i\n", token->type);
		}
		i++;
	}
}

static void	clear_token(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	free(token->value);
	free(token);
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
		if (tmp[i] != NULL)
			token->value = tmp[i];
		else
			token->value = "";
		printf("Token:\n  Value: %s\n  Type: %i\n", token->value, token->type);
		ft_vec_push(&tokens, (void *)token);
		i++;
	}
	pretty_print_vector(&tokens);
	ft_vec_free(&tokens, clear_token);
	ft_vec_init(&tokens, 5, sizeof(t_token));
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_vector	tokens;

	(void)ac;
	(void)av;
	(void)env;
	ft_vec_init(&tokens, 1, sizeof(t_token));
	while (1)
	{
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
	}
	return (0);
}
