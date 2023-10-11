/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 14:04:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/07 18:26:58 by mdekker/jde   ########   odam.nl         */
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

/**
 * @note	check if dup_fd or redirects should be done for the built_in
 */
void	exec_built_in(t_group *group, t_process type)
{
	dup_fd(group, type);
	if (is_special_builtin(group->cmd))
		ghost_exec(group, type);
	else if (ft_strcmp(group->cmd, "echo") == 0)
		ft_echo(group);
	else if (ft_strcmp(group->cmd, "pwd") == 0)
		ft_pwd(group);
	else if (ft_strcmp(group->cmd, "env") == 0)
		ft_exit(group);
}

void	exec_special_builtin(t_group *group)
{
	if (ft_strcmp(group->cmd, "exit") == 0)
		ft_exit(group);
	else if (ft_strcmp(group->cmd, "cd") == 0)
		ft_cd(group);
	else if (ft_strcmp(group->cmd, "export") == 0)
		ft_export(group);
	else if (ft_strcmp(group->cmd, "unset") == 0)
		ft_unset(group);
}
