/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   placeholder_special.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 15:01:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/04 16:50:45 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

void	ft_exit(t_group *group)
{
	size_t	i;

	i = 0;
	while (group->args[i])
		i++;
	if (i == 1)
	{
		group->data->exit_shell = true;
		g_signal.exit_status = 0;
		return ;
	}
	if (i > 2)
	{
		write(1, "minishell: exit: too many arguments\n", 37);
		g_signal.exit_status = 1;
		return ;
	}
	i = 0;
	while (group->args[1][i])
	{
		if (!ft_isdigit(group->args[1][i]))
		{
			write(1, "minishell: exit: ", 17);
			write(1, group->args[1], ft_strlen(group->args[1]));
			write(1, ": numeric argument required\n", 28);
			g_signal.exit_status = 2;
			return ;
		}
		i++;
	}
	g_signal.exit_status = ft_atoi(group->args[1]);
	group->data->exit_shell = true;
}

void	ft_cd(t_group *group)
{
	(void)group;
	printf("built_in cd placeholder\n");
	g_signal.exit_status = 0;
}

void	ft_export(t_group *group)
{
	(void)group;
	printf("built_in export placeholder\n");
	g_signal.exit_status = 0;
}

void	ft_unset(t_group *group)
{
	(void)group;
	printf("built_in unset placeholder\n");
	g_signal.exit_status = 0;
}