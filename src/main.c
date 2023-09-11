/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/11 11:21:07 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_signal	g_signal;

static void	check_leaks(void)
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

/**
 * @brief The main loop of the program
 *
 * @param vec The vector to store the token_vec in
 */
// static void	loop(t_vector *vec)
// {
// 	char	*input;

// 	while (1)
// 	{
// 		input = readline("\n\033[1;32mminishell$ \033[0m");
// 		if (!input)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		add_history(input);
// 		if (!ft_strcmp(input, "exit"))
// 			return (free(input), free_global(true));
// 		else
// 		{
// 			if (!lexer(input, vec))
// 				return (free(input), free_global(true));
// 			parser(vec);
// 			print_vector(vec, print_token);
// 		}
// 		free(input);
// 		free_global(false);
// 		vec_init(vec, 5, sizeof(t_token), clear_token);
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_shell	*data;

	// t_found	**found;
	if (DEBUG)
		debug();
	data = init_shell(env, true);
	if (ac == 2)
	{
		if (!lexer(av[1], data))
			write_err(data);
		if (!parser(data))
			write_err(data);
		if (!operator_split(data))
			write_err(data);
		// might need to test op_split
		if (!parser(data))
			write_err(data);
		// expansion based on env vector
		// combine redirects+heredoc into 1 token + verify_token_vec combined
		// verify_token_vec(data);
		if (!group_token_vec(data))
			write_err(data);
		// alles tot hier zou moeten werken, exec doe ik zondag
		// check if all groups are properly cerated
		if (!executor(data->exec))
			write_err(data);
		// if (data->exit_shell)
		// {
		return (free_shell(data, true), g_signal.exit_status);
		// }
		// else
		// 	free_shell(data, false);
		return (0); // change this to return built_in_exit
	}
	// else if (ac == 1)
	// 	loop(data);
	else
	{
		printf("Too many arguments");
		free_shell(data, true);
	}
	return (0);
}
