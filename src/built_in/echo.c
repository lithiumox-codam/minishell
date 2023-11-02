/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:10:23 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/02 21:02:08 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

static bool	check_flag(char **args)
{
	return (args[1] && ft_strcmp(args[1], "-n") == 0);
}

void	ft_echo(t_group *group)
{
	size_t i;

	if (group->args[1] && ft_strncmp(group->args[1], "-n", 2) == 0)
		i = 2;
	else
		i = 1;
	while (group->args[i])
	{
		write(1, group->args[i], ft_strlen(group->args[i]));
		if (group->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (group->args[1] && ft_strcmp(group->args[1], "-n") != 0)
		write(1, "\n", 1);
	exit(0);
}
