/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:10:23 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/16 19:05:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

/**
 * @brief Checks if a flag only contains n's and if it does, it will return the
 * index of the first non-flag argument or 1 if no flags.
 *
 * @param group The group struct with the args
 * @return size_t The index of the first non-flag argument or 1 if no flags
 */
static size_t	check_flags(t_group *group)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (group->args[i])
	{
		j = 1;
		if (group->args[i][0] != '-')
			return (i);
		while (group->args[i][j] == 'n')
			j++;
		if (group->args[i][j] != '\0')
			return (i);
		i++;
	}
	return (1);
}

/**
 * @brief Prints the arguments of the echo command
 * @param group The group struct with the args
 * @return void
 */
void	ft_echo(t_group *group)
{
	size_t	i;

	i = check_flags(group);
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
