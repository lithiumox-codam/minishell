/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 20:50:26 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_signal	signal;

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
	t_shell *data;
	pid_t pid;
	int status;

	// t_found	**found;
	if (DEBUG)
		debug();
	data = init_shell(env, true);
	if (ac == 2)
	{
		pid = fork();
		if (pid == -1)
			exit_mini("initial fork failed", errno);
		if (pid == 0)
		{
			if (!lexer(av[1], data))
				err();
			// lexer retester
			parser(data);
			// parser retesting
			operator_split(data);
			// operator split retesting
			verify_token_vec(data);
			// check if it really catches all doubles
			group_token_vec(data);
			// check if all groups are properly cerated
			status = executor(data->exec);
			free_shell(data, true);
			exit(status);
		}
		if (waitpid(pid, &status, 0) == -1)
			exit_mini("waitpid failed", errno);
		if (WEXITSTATUS(status) == 10)
		{
			return (10); // pipe workaround
			signal.exit_status = WEXITSTATUS(status);
			// found = g_data.token_vec.find(&g_data.token_vec, find_strings);
			// if (!found)
			// {
			// 	printf("%zu counted\n",
					g_data.token_vec.count(&g_data.token_vec,
			// 				find_strings));
			// 	printf("No matches found\n");
			// }
			// else
			// {
			// 	printf("Printing matches:\n");
			// 	while (*found)
			// 	{
			// 		print_token((*found)->item, (*found)->index);
			// 		free(*found);
			// 		found++;
			// 	}
			// 	free(found);
			// }
			// if (DEBUG)
			print_vector(&data->token_vec, print_token);
			// print_vector(&g_data.env, print_env);
			free_shell(data, true);
			return (0);
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
