
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:10:23 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/21 15:39:55 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
	* @brief Checks if a flag only contains n's and if it does,
		it will return the
	* index of the first non-flag argument or 1 if no flags.
	*
	* @param group The group struct with the args
	* @return size_t The index of the first non-flag argument or 1 if no flags
	*/
static bool	check_flag(char *arg, bool *flag)
{
	size_t	i;

	i = 0;
	if (arg[i] != '-')
		return (false);
	else
		i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
	{
		*flag = true;
		return (true);
	}
	return (false);
}

/**
 * @brief Prints the arguments of the echo command
 * @param group The group struct with the args
 * @return void
 */
void	ft_echo(t_group *group)
{
	size_t	i;
	bool	flag;

	i = 1;
	flag = false;
	while (group->args[i] && check_flag(group->args[i], &flag))
		i++;
	while (group->args[i])
	{
		write(1, group->args[i], ft_strlen(group->args[i]));
		if (group->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	exit(0);
}
