/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/14 10:34:32 by mdekker/jde   ########   odam.nl         */
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
static int	loop(t_shell *data)
{
	char	*input;
	bool	exit_shell;

	exit_shell = false;
	while (1)
	{
		input = readline("minishell\n❯ ");
		if (!input || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (!lexer(input, data))
		{
			write_err(data);
			free(input);
			free_shell(data, false);
			vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
			continue ;
		}
		if (!parser(data))
		{
			write_err(data);
			free(input);
			free_shell(data, false);
			vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
			continue ;
		}
		if (!operator_split(data))
		{
			write_err(data);
			free(input);
			free_shell(data, false);
			vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
			continue ;
		}
		if (!check_tokens(data))
		{
			write_err(data);
			free(input);
			free_shell(data, false);
			vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
			continue ;
		}
		if (!group_token_vec(data))
		{
			write_err(data);
			free(input);
			free_shell(data, false);
			vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
			continue ;
		}
		if (!executor(data, &exit_shell))
		{
			write_err(data);
			free(input);
			free_shell(data, false);
			vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
			continue ;
		}
		free(input);
		if (exit_shell == true)
			return (free_shell(data, true), g_signal.exit_status);
		free_shell(data, false);
		vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*data;
	bool 	exit_shell;

	exit_shell = false;
	if (DEBUG)
		debug();
	data = init_shell(env, true);
	if (ac == 2)
	{
		if (!lexer(av[1], data))
			return (write_err(data), free_shell(data, true),
				g_signal.exit_status);
		if (!parser(data))
			return (write_err(data), free_shell(data, true),
				g_signal.exit_status);
		if (!operator_split(data))
			return (write_err(data), free_shell(data, true),
				g_signal.exit_status);
		if (!check_tokens(data))
			return (write_err(data), free_shell(data, true),
				g_signal.exit_status);
		if (!group_token_vec(data))
			return (write_err(data), free_shell(data, true),
				g_signal.exit_status);
		if (!executor(data, &exit_shell))
			return (write_err(data), free_shell(data, true),
				g_signal.exit_status);
		free_shell(data, true);
		return (0); // change this to return built_in_exit
	}
	else if (ac == 1)
		return (loop(data));
	else
	{
		printf("Too many arguments");
		free_shell(data, true);
	}
	return (0);
}
