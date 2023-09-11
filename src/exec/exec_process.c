/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:08:08 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/11 20:13:14 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_start(t_process type, t_group *group)
{
	if (type == LEFT)
	{
		if (close(group->right_pipe[0]) == -1)
			perror("minishell: ");
	}
	else if (type == RIGHT)
	{
		if (close(group->left_pipe[1]) == -1)
			perror("minishell: ");
	}
	else if (type == MIDDLE)
	{
		if (close(group->left_pipe[1]) == -1)
			perror("minishell: ");
		if (close(group->right_pipe[0]) == -1)
			perror("minishell: ");
	}
}

static void	dup_fd(t_group *group, t_process type)
{
	if (type == SINGLE)
		return ;
	else if (type == LEFT)
	{
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			perror("minishell: ");
	}
	else if (type == RIGHT)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			perror("minishell: ");
	}
	else if (type == MIDDLE)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			perror("minishell: ");
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			perror("minishell: ");
	}
}

void	exec_process(t_group *group, t_process type)
{
	size_t	i;
	char	**env;

	close_start(type, group);
	if (is_built_in(group->cmd))
		exec_built_in(group, type);
	check_cmd(group);
	handle_redirects(group);
	dup_fd(group, type);
	exec_built_in(group, type);
	env = combine_env(&group->data->env);
	execve(group->cmd, group->args, env);
}

void	exec_absolut_path(t_group *group)
{
	char **env;

	if (access(group->cmd, X_OK) != 0)
		exec_err(group->cmd, PERMISSION);
	handle_redirects(group);
	env = combine_env(&group->data->env);
	execve(group->cmd, group->args, env);
}