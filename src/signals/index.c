/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 11:36:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/19 14:39:04 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

void	signal_main(int signal_num)
{
	if (signal_num == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_hdoc(int signal_num)
{
	if (signal_num == SIGINT)
	{
		g_signal.inte = true;
		printf("\n");
	}
}

void	signal_child(int signal_num)
{
	(void)signal_num;
}
