/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/16 17:38:30 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	tokenize(char *input, t_vector tokens)
{
	char	**tmp;
	t_token	*token;

	tmp = ft_split(input, ' ');
	while (*tmp)
	{
		printf("tmp: %s\n", *tmp);
		token = malloc(sizeof(t_token));
		printf("token: %p\n", token);
		token->type = STRING;
		token->value = *tmp;
		printf("token->value: %s\n", token->value);
		printf("tokens.size: %zu\n", tokens.size);
		ft_vec_push(&tokens, (void *)token);
		printf("tokens.size: %zu\n", tokens.size);
		free(*tmp);
		tmp++;
	}
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_vector	tokens;
	t_token		*token;

	(void)ac;
	(void)av;
	(void)env;
	ft_vec_init(&tokens, 5, sizeof(t_token));
	// print the address of the vector
	printf("tokens: %p\n", &tokens);
	// print the vavtor type_size and size
	printf("tokens.type_size: %zu\n", tokens.type_size);
	printf("tokens.size: %zu\n", tokens.size);
	printf("\033[1;32mWelcome to minishell!\033[0m\n");
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
		printf("tokens.size: %zu\n", tokens.size);
		printf("tokens.type_size: %zu\n", tokens.type_size);
		token = ft_vec_get(&tokens, 1);
		free(input);
	}
	return (0);
}
