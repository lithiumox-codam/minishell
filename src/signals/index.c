/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 11:36:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/17 19:34:54 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	}
}

void	signal_child(int signal_num)
{
	(void)signal_num;
}
