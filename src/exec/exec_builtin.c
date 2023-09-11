/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 14:04:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/11 20:14:03 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief closes the pipes of the groups and exits(0)
 */
static void	ghost_exec(t_group *group, t_process type)
{
	if (type == LEFT)
	{
		if (close(group->right_pipe[1]) == -1)
			perror("minishell: ");
	}
	else if (type == RIGHT)
	{
		if (close(group->left_pipe[0]) == -1)
			perror("minishell: ");
	}
	else if (type == MIDDLE)
	{
		if (close(group->left_pipe[0]) == -1)
			perror("minishell: ");
		if (close(group->right_pipe[1]) == -1)
			perror("minishell: ");
	}
	exit(0);
}

void	exec_built_in(t_group *group, t_process type)
{
	dup_fd(group, type);
	//@note check if dup_Fd is necessary for builtins
	if (is_special_built_in(group->cmd))
		ghost_exec(group, type);
	else if (ft_strcmp(group->cmd[0], "echo") == 0)
		ft_echo(group);
	else if (ft_strcmp(group->cmd[0], "pwd") == 0)
		ft_pwd(group);
	else if (ft_strcmp(group->cmd[0], "env") == 0)
		ft_env(group);
	else if (ft_strcmp(group->cmd[0], "exit") == 0)
		ft_exit(group);
}
