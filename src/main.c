/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/01 21:07:36 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_global	g_data;

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
 * @param vec The vector to store the tokens in
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
				return (free(input), free_global(true));
			parser(vec);
			print_vector(vec, print_token);
		}
		free(input);
		free_global(false);
		vec_init(vec, 5, sizeof(t_token), clear_token);
	}
}

// static bool	find_strings(void *data)
// {
// 	t_token	*token;

// 	token = (t_token *)data;
// 	if (token->type == STRING)
// 		return (true);
// 	return (false);
// }

int	main(int ac, char **av, char **env)
{
	t_exec	*exec;
	pid_t	pid;
	int		status;

	// t_found	**found;
	if (DEBUG)
		debug();
	if (!init(env))
		return (1);
	if (ac == 2)
	{
		pid = fork();
		if (pid == -1)
			exit_mini("initial fork failed", errno);
		if (pid == 0)
		{
			if (!lexer(av[1], &g_data.tokens))
				mini_exit("lexer failed", 1);
			parser(&g_data.tokens);
			printf("Parsed!\n");
			if (!operator_split(&g_data.tokens))
				mini_exit("operator split failed", 1);
			
			verify_tokens(&g_data.tokens);
			exec = group_tokens(&g_data.tokens, env);
			status = executor(exec);
			printf("succes, status=%i\n", status);
			exit(status);
		}
		if (waitpid(pid, &status, 0) == -1)
			exit_mini("waitpid failed", errno);
		g_data.exit_status = WEXITSTATUS(status);
		// found = g_data.tokens.find(&g_data.tokens, find_strings);
		// if (!found)
		// {
		// 	printf("%zu counted\n", g_data.tokens.count(&g_data.tokens,
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
		print_vector(&g_data.tokens, print_token);
		// print_vector(&g_data.env, print_env);
		free_global(true);
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
