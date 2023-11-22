/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:08:08 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 16:18:12 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_unused(t_process type, t_group *group)
{
	if (type == SINGLE)
		return ;
	if (type == LEFT || type == MIDDLE)
	{
		if (close(group->right_pipe[0]) == -1)
			perror("minishell: right_pipe[0]");
	}
	if (type == RIGHT || type == MIDDLE)
	{
		if (close(group->left_pipe[1]) == -1)
			perror("minishell: left_pipe[1]");
	}
}

static void	dup_redirects(t_group *group)
{
	if (group->in_red != -1)
	{
		if (dup2(group->in_red, STDIN_FILENO) == -1)
			perror("minishell: in_red");
	}
	if (group->out_red != -1)
	{
		if (dup2(group->out_red, STDOUT_FILENO) == -1)
			perror("minishell: out_red");
	}
}

void	dup_fd(t_group *group, t_process type)
{
	if (type == SINGLE)
	{
		dup_redirects(group);
		return ;
	}
	if (type == LEFT || type == MIDDLE)
	{
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			perror("minishell: right_pipe[1]");
		if (close(group->right_pipe[1]) == -1)
			perror("minishell");
	}
	if (type == RIGHT || type == MIDDLE)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			perror("minishell: left_pipe[0]");
		if (close(group->left_pipe[0]) == -1)
			perror("minishell: left_pipe[0]");
	}
	dup_redirects(group);
}

void	exec_process(t_group *group, t_process type, t_shell *data)
{
	char	**env;

	close_unused(type, group);
	handle_redirects(group);
	if (group->cmd == NULL)
		exit(0);
	if (is_builtin(group->cmd))
		exec_built_in(group, type, data);
	check_cmd(group, type, &data->env);
	env = combine_env(&data->env);
	dup_fd(group, type);
	if (!execve(group->cmd, group->args, env))
		exec_err(NULL, PERR);
}

void	exec_absolute_path(t_group *group, t_process type, t_vector *env_vec)
{
	char	**env;

	if (access(group->cmd, X_OK) != 0)
		exec_err(group->cmd, PERMISSION);
	env = combine_env(env_vec);
	dup_fd(group, type);
	if (!execve(group->cmd, group->args, env))
		exec_err(NULL, PERR);
}
