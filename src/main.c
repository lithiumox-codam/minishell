/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 02:49:36 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_data;

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

static bool	token_is_pipe(void *data)
{
	t_token	*token;

	token = (t_token *)data;
	return (token->type == PIPE);
}

/**
 * @brief The main loop of the program
 *
 * @param vec The vector to store the tokens in
 *
 * @todo Add a way to exit the program but not the shell
 */
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
				return (free(input), ft_vec_free(vec, clear_token));
			parser(vec);
			print_token_vector(vec);
		}
		free(input);
		printf("\n\n\n\amount of pipes: %zu\n\n\n", ft_vec_count(vec,
					token_is_pipe));
		ft_vec_free(vec, clear_token);
		ft_vec_init(vec, 5, sizeof(t_token), clear_token);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)env;
	if (DEBUG)
		debug();
	init();
	if (ac == 2)
	{
		if (!lexer(av[1], &g_data.tokens))
			return (ft_vec_free(&g_data.tokens, clear_token), 1);
		parser(&g_data.tokens);
		print_token_vector(&g_data.tokens);
		printf("\n\n\n\amount of pipes: %zu\n\n\n", ft_vec_count(&g_data.tokens,
					token_is_pipe));
		ft_vec_free(&g_data.tokens, clear_token);
		return (0);
	}
	else if (ac == 1)
		loop(&g_data.tokens);
	else
	{
		printf("Too many arguments");
		ft_vec_free(&g_data.tokens, clear_token);
	}
	return (0);
}
