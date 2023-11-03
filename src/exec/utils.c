/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 19:44:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/03 18:50:03 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "echo") == 0)
		return (true);
	return (false);
}

bool	is_special_builtin(char *str)
{
	if (ft_strcmp(str, "exit") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "cd") == 0)
		return (true);
	return (false);
}
