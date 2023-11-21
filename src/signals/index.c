/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 11:36:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 00:16:17 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

void	signal_main(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief	sets up signal handling and avoid readline catching sigs
 * @note	SIGINT = Ctrl-C
 * @note	SIGQUIT = Ctrl-\
 */
void	setup_hdoc_signals(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, signal_hdoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_hdoc(int signal_num)
{
	if (signal_num == SIGINT)
	{
		exit(130);
	}
}

void	setup_child_signals(void)
{
	signal(SIGINT, signal_child);
	signal(SIGQUIT, signal_child);
}

void	signal_child(int signal_num)
{
	if (signal_num == SIGINT)
	{
		write(1, "\n", 1);
	}
	else if (signal_num == SIGQUIT)
	{
		write(1, "Quit\n", 5);
	}
}
