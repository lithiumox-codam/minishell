/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:08:08 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/01 22:26:59 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_data;

void	exec_process(t_group *group, t_process type)
{
	size_t	i;
	char	*str;
	char	**env;

	close_start(type, group);
	group->cmd = combine_cmd(group); //@note for first command remove quotes
	if (is_built_in(group->cmd[0]))
		exec_built_in(group, type, &g_data.env);
	check_cmd(group->cmd[0], &g_data.env);
	handle_redirects(group);
	dup_fd(type, group);
	exec_built_in(str, group->cmd, &g_data.env);
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
	handle_redirects(group);
	dup_fd(type, group);
	if (ft_strcmp(group->cmd[0], "exit") == 0)
		ft_exec_exit(group->cmd, type); //@note create built in for exit
	if (ft_strcmp(group->cmd[0], "echo") == 0)
		ft_echo(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "cd") == 0)
		ft_cd(group->cmd[0], group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "pwd") == 0)
		ft_pwd(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "export") == 0)
		ft_export(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "unset") == 0)
		ft_unset(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "env") == 0)
		ft_env(group->cmd, env);
	else if (ft_strcmp(group->cmd[0], "exit") == 0)
		ft_exit(group->cmd, env);
}
