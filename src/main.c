/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 17:45:26 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_data;

void	check_leaks(void)
{
	printf("\033[1;10m●\n");
	printf("\033[1;12m│\n");
	printf("├── Checking for leaks 💦\n");
	printf("\033[1;12m│\n");
	printf("\033[0m\n");
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

// static bool	token_is_pipe(void *data)
// {
// 	t_token	*token;

// 	token = (t_token *)data;
// 	return (token->type == PIPE);
// }

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
			return (free(input), free_global(true));
		else
		{
			if (!lexer(input, vec))
				return (free(input), ft_vec_free(vec));
			parser(vec);
			print_vector(vec, print_token);
		}
		free(input);
		free_global(false);
		ft_vec_init(vec, 5, sizeof(t_token), clear_token);
	}
}

int	main(int ac, char **av, char **env)
{
	if (DEBUG)
		debug();
	init(env);
	if (ac == 2)
	{
		if (!lexer(av[1], &g_data.tokens))
			return (ft_vec_free(&g_data.tokens), 1);
		parser(&g_data.tokens);
		print_vector(&g_data.tokens, print_token);
		if (DEBUG)
			print_vector(&g_data.env, print_env);
		free_global(false);
		return (0);
	}
	else if (ac == 1)
		loop(&g_data.tokens);
	else
	{
		printf("Too many arguments");
		free_global(true);
	}
	return (0);
}
