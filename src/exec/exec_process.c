/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:08:08 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/11 12:58:40 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_process(t_group *group, t_process type)
{
	size_t	i;
	char	**env;

	close_start(type, group);
	if (is_built_in(group->cmd))
		exec_built_in(group, type);
	check_cmd(cmd, (&group->data)->env);
	handle_redirects(group);
	dup_fd(type, group);
	exec_built_in(group);
	env = combine_env(&g_data.env);
	execve(str, group->cmd, env);
}

static void	close_start(t_process type, t_group *group)
{
	if (type == LEFT)
	{
		if (close(group->right_pipe[0]) == -1)
			err(PERROR, 1, NULL, NULL);
	}
	else if (type == RIGHT)
	{
		if (close(group->left_pipe[1]) == -1)
			err(PERROR, 1, NULL, NULL);
	}
	else if (type == MIDDLE)
	{
		if (close(group->left_pipe[1]) == -1)
			err(PERROR, 1, NULL, NULL);
		if (close(group->right_pipe[0]) == -1)
			err(PERROR, 1, NULL, NULL);
	}
}

static void	dup_fd(t_process type, t_group *group)
{
	if (type == SINGLE)
		return ;
	else if (type == LEFT)
	{
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			err(PERROR, 1, NULL, NULL);
	}
	else if (type == RIGHT)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			err(PERROR, 1, NULL, NULL);
	}
	else if (type == MIDDLE)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			err(PERROR, 1, NULL, NULL);
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			err(PERROR, 1, NULL, NULL);
	}
}

static void	exec_built_in(t_group *group, t_process type, t_vector *env)
{
	dup_fd(type, group);
	//@note check if it should maybe only be done for outfiles?
	// for the calls of the builtins just pass the entire group as paramater so they can read their own indirects
	if (is_special_built_in(group))
		ghost_exec(group);
	else if (ft_strcmp(group->cmd[0], "echo") == 0)
		ft_echo(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "pwd") == 0)
		ft_pwd(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "env") == 0)
		ft_env(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "exit") == 0)
		ft_exit(group->cmd, env);
}
