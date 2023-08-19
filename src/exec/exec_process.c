/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_process.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:08:08 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/19 17:54:16 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_data;

void	exec_process(t_process type, t_group *group, char **envp)
{
	size_t	i;
	char	*str;
	t_token	*token;

	close_start(type, group);
	token = ft_vector_get(&group->input, 0);
	handle_redirects(group);
	group->cmd = combine_tokens(&group->input);
	if (!group->cmd)
		err("malloc error", 1, NULL);
	str = rm_quotes(token->value);
	if (!str)
		err("malloc error", 1, NULL);
	check_cmd(str);
	dup_fd(type, group);
	built_in(str, group->cmd, &g_data.env);
	execve(str, group->cmd, envp);
}

static void	close_start(t_process type, t_group *group)
{
	if (type == LEFT)
	{
		if (close(group->right_pipe[0]) == -1)
			err(PERROR, 1, NULL);
	}
	else if (type == RIGHT)
	{
		if (close(group->left_pipe[1]) == -1)
			err(PERROR, 1, NULL);
	}
	else if (type == MIDDLE)
	{
		if (close(group->left_pipe[1]) == -1)
			err(PERROR, 1, NULL);
		if (close(group->right_pipe[0]) == -1)
			err(PERROR, 1, NULL);
	}
}

static void	dup_fd(t_process type, t_group *group)
{
	if (type == LEFT)
	{
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			err(PERROR, 1, NULL);
	}
	else if (type == RIGHT)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			err(PERROR, 1, NULL);
	}
	else if (type == MIDDLE)
	{
		if (dup2(group->left_pipe[0], STDIN_FILENO) == -1)
			err(PERROR, 1, NULL);
		if (dup2(group->right_pipe[1], STDOUT_FILENO) == -1)
			err(PERROR, 1, NULL);
	}
}

static void	built_in(char *str, char **cmd, t_vector *env)
{
	if (ft_strcmp(str, "echo") == 0)
		ft_echo(str, cmd, env);
	else if (ft_strcmp(str, "cd") == 0)
		ft_cd(str, cmd, env);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(str, cmd, env);
	else if (ft_strcmp(str, "export") == 0)
		ft_export(str, cmd, env);
	else if (ft_strcmp(str, "unset") == 0)
		ft_unset(str, cmd, env);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(str, cmd, env);
	else if (ft_strcmp(str, "exit") == 0)
		ft_exit(str, cmd, env);
}
