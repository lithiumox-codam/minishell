/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 10:10:23 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/23 10:12:00 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

static bool	check_flag(char **args)
{
	return (args[1] && ft_strcmp(args[1], "-n") == 0);
}
