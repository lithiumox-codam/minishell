/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 15:01:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/17 15:25:17 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

int long long	ft_exit_atoi(char *str)
{
	size_t			i;
	int long long	output;

	output = 0;
	i = 0;
	while (checkchar(str[i], "1234567890"))
	{
		output = (output * 10) + (str[i] - '0');
		i++;
	}
	return (output);
}

static bool	check_args(t_group *group, t_shell *data)
{
	if (group->args[1] == NULL)
	{
		free_shell(data, true);
		exit(0);
	}
	if (group->args[2] != NULL)
	{
		write(1, "minishell: exit: too many arguments\n", 37);
		g_signal.exit_status = 1;
		return (false);
	}
	return (true);
}

/**
 * @brief The exit command will exit the shell with the given exit code.
 *
 * @param group The group struct with the args
 * @param data The shell struct
 * @return void
 */
void	ft_exit(t_group *group, t_shell *data)
{
	size_t			i;
	int long long	output;

	i = 0;
	if (!check_args(group, data))
		return ;
	while (group->args[1][i])
	{
		if (!ft_isdigit(group->args[1][i]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				group->args[1]);
			g_signal.exit_status = 2;
			return ;
		}
		i++;
	}
	output = ft_exit_atoi(group->args[1]);
	free_shell(data, true);
	exit(output);
}
