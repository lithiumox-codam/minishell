/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/04 01:01:58 by mdekker/jde   ########   odam.nl         */
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
static void	loop(t_shell *data)
{
	char	*input;

	while (1)
	{
		input = readline("\n\033[1;32mminishell\n❯ \033[0m");
		if (!input)
		{
			free(input);
			break ;
		}
		add_history(input);
		if (!ft_strcmp(input, "exit"))
			return (free(input), free_shell(data, true));
		else
		{
			if (!lexer(input, data))
				write_err(data);
			if (!parser(data))
				write_err(data);
			if (!operator_split(data))
				write_err(data);
			if (!check_tokens(data))
				write_err(data);
			print_vector(&data->token_vec, print_token);
			if (!group_token_vec(data))
				write_err(data);
			print_group(data);
		}
		free(input);
		free_shell(data, false);
		vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*data;

	if (DEBUG)
		debug();
	data = init_shell(env, true);
	if (ac == 2)
	{
		if (!lexer(av[1], data))
			return (write_err(data), g_signal.exit_status);
		if (!parser(data))
			return (write_err(data), g_signal.exit_status);
		if (!operator_split(data))
			return (write_err(data), g_signal.exit_status);
		if (!check_tokens(data))
			return (write_err(data), g_signal.exit_status);
		print_vector(&data->token_vec, print_token);
		if (!group_token_vec(data))
			return (write_err(data), g_signal.exit_status);
		print_group(data);
		free_shell(data, true);
		return (0); // change this to return built_in_exit
	}
	else if (ac == 1)
		loop(data);
	else
	{
		printf("Too many arguments");
		free_shell(data, true);
	}
	return (0);
}
