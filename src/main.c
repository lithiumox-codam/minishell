/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/26 17:41:59 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_signal	g_signal;

static void	debug(void)
{
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

	if (DEBUG)
		debug();
	data = init_shell(env, true);
	if (ac == 2)
	{
		if (!lexer(av[1], data))
			write_err(data);
		parser(data);
		print_vector(&data->token_vec, print_token);
		operator_split(data);
		if (!check_tokens(data))
			return (write_err(data), free_shell(data, true), 1);
		print_vector(&data->token_vec, print_token);
		// combine redirects+heredoc into 1 token + verify_token_vec combined
		// verify_token_vec(data);
		// expansion based on env vector
		// group_token_vec(data);
		// // check if all groups are properly cerated
		// executor(data->exec);
		free_shell(data, true);
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
