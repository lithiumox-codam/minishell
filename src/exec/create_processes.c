/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 12:40:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/12 20:17:37 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool set_pipe(t_group *group, size_t i, size_t count, t_shell *data)
{
	t_group *next_group;

	if (i < count - 1)
	{
		if (pipe(group->right_pipe) != 0)
			return (false);
		next_group = vec_get(&data->exec->group_vec, i + 1);
		next_group->left_pipe[0] = group->right_pipe[0];
		next_group->left_pipe[1] = group->right_pipe[1];		
	}
	return (true);
}

static void call_process (t_group *group, size_t i, size_t count,t_shell *data)
{
	if (i == 0)
		exec_process(group, LEFT, (&data->env));
	else if ((i == 1 && count == 2) || (count > 2 && i == count - 1))
		exec_process(group, RIGHT, (&data->env));
	else
		exec_process(group, MIDDLE, (&data->env));
}

static void set_group_and_close(t_group *group, pid_t pid, size_t i)
{
	group->pd = pid;
	if (i != 0)
	{
		if (close(group->left_pipe[0]) == -1)
			perror("minishell: close_pipes");
		if (close(group->left_pipe[1]) == -1)
			perror("minishell: close_pipes");
	}
}

static bool	fork_and_pipe(t_shell *data)
{
	size_t	i;
	size_t 	count;
	pid_t	pid;
	t_group	*group;

	count = (&data->exec->group_vec)->length;
	i = 0;
	while (i < count)
	{
		group = vec_get(&data->exec->group_vec, i);
		if (!set_pipe(group, i, count, data))
			return (set_err(PERR, NULL, data), false);
		pid = fork();
		if (pid == -1)
			return (set_err(PERR, NULL, data));
		if (pid == 0)
			call_process(group, i, count, data);
		else
			set_group_and_close(group, pid, i);
		i++;
	}
	return (true);
}

/**
 * @brief Creates the processes and pipes for the execution
 */
bool	create_processes(t_shell *data)
{
	t_vector	*group_vec;
	t_group		*group;

	group_vec = &data->exec->group_vec;
	if (group_vec->length == 1)
	{
		group = vec_get(group_vec, 0);
		group->pd = fork();
		if (group->pd == -1)
			return (set_err(PERR, NULL, data));
		if (group->pd == 0)
			exec_process(group, SINGLE, (&data->env));
	}
	else
		fork_and_pipe(data);
	return (true);
}
