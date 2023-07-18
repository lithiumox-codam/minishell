/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/18 12:27:28 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pretty_print_vector(t_vector *tokens)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (i < tokens->lenght)
	{
		token = (t_token *)ft_vec_get(tokens, i);
		if (token != NULL)
		{
			printf("\033[1;32m●\n");
			printf("\033[1;34m│\n");
			printf("├── Token %zu:\n", i);
			printf("│   ├── Value: %s\n", token->value);
			printf("│   ├── Type: %i\n", token->type);
			printf("│   └── Adress: %p\n", token);
			printf("\033[1;34m│\n");
			printf("\033[0m");
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
	t_token	token;
	size_t	i;

	i = 0;
	tmp = ft_split(input, ' ');
	while (tmp[i])
	{
		token.type = DOUBLE_QUOTE;
		if (i % 2)
			token.type = SINGLE_QUOTE;
		token.value = tmp[i];
		ft_vec_push(&tokens, (void *)&token);
		i++;
	}
	free(tmp);
	pretty_print_vector(&tokens);
	ft_vec_free(&tokens, clear_token);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_vector	tokens;

	(void)env;
	ft_vec_init(&tokens, 5, sizeof(t_token));
	if (ac == 2)
	{
		tokenize(av[1], tokens);
		return (0);
	}
	while (1)
	{
		input = readline("\n\033[1;32mminishell$ \033[0m");
		if (!input)
			break ;
		add_history(input);
		if (!ft_strcmp(input, "exit"))
			return (free(input), 0);
		else
			tokenize(input, tokens);
		free(input);
		ft_vec_init(&tokens, 5, sizeof(t_token));
	}
	return (0);
}
