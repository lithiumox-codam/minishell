/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 15:51:07 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_leaks(void)
{
	system("leaks minishell");
}

static void	debug(void)
{
	atexit(check_leaks);
	printf("\033[1;32m●\n");
	printf("\033[1;34m│\n");
	printf("├── Debug mode enabled\n");
	printf("\033[1;34m│\n");
	printf("\033[0m");
}

static void	loop(t_vector *vec)
{
	char	*input;

	while (1)
	{
		input = readline("\n\033[1;32mminishell$ \033[0m");
		if (!input)
		{
			free(input);
			break ;
		}
		add_history(input);
		if (!ft_strcmp(input, "exit"))
			return (free(input), ft_vec_free(vec, clear_token));
		else
		{
			if (!lexer(input, vec))
				printf("lexer error");
			parser(vec);
			print_token_vector(vec);
		}
		free(input);
		ft_vec_free(vec, clear_token);
		ft_vec_init(vec, 5, sizeof(t_token));
	}
}

int	main(int ac, char **av, char **env)
{
	t_vector	tokens;

	(void)env;
	if (DEBUG)
		debug();
	ft_vec_init(&tokens, 5, sizeof(t_token));
	if (ac == 2)
	{
		if (!lexer(av[1], &tokens))
		{
			printf("lexer error");
			return (1);
		}
		parser(&tokens);
		print_token_vector(&tokens);
		ft_vec_free(&tokens, clear_token);
		return (0);
	}
	else if (ac == 1)
		loop(&tokens);
	else
	{
		printf("Too many arguments");
		ft_vec_free(&tokens, clear_token);
	}
	return (0);
}
