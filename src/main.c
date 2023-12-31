/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/12 14:11:01 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/23 14:34:15 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief	sets up signal handling and avoid readline catching sigs
 * @note	SIGINT = Ctrl-C
 * @note	SIGQUIT = Ctrl-\
 */
static void	setup_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_main);
	signal(SIGQUIT, SIG_IGN);
}

static void	soft_exit(char *input, t_shell *data)
{
	write_err(data);
	free(input);
	free_shell(data, false);
	vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
}

static bool	function_map(char *input, t_shell *data)
{
	int			i;
	static bool	(*function[5])(t_shell *);

	function[0] = parser;
	function[1] = check_tokens;
	function[2] = expand_tokens;
	function[3] = group_token_vec;
	function[4] = executor;
	if (!lexer(input, data))
		return (soft_exit(input, data), false);
	i = -1;
	while (i++ < 4)
	{
		if (!function[i](data))
			return (soft_exit(input, data), false);
	}
	return (true);
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
		setup_signals();
		input = readline(" ❯ ");
		if (input == NULL)
		{
			free_shell(data, true);
			printf("exit\n");
			exit(0);
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (!function_map(input, data))
			continue ;
		free(input);
		free_shell(data, false);
		vec_init(&data->token_vec, 5, sizeof(t_token), clear_token);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*data;

	(void)av;
	if (ac != 1)
	{
		write(2, "Too maaaaaaaaaaany arguments\n", 20);
		return (1);
	}
	data = init_shell(env, true);
	loop(data);
	return (0);
}
