/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 12:40:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/07 22:25:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	add_pipes(t_vector *group_vec, size_t process_count, t_shell *data)
{
	size_t	i;
	t_group	*group;
	t_group	*next_group;

	i = 0;
	while (i < process_count - 1)
	{
		group = vec_get(group_vec, i);
		if (pipe(group->right_pipe) != 0)
			return (set_err(PERR, NULL, data));
		next_group = vec_get(group_vec, i + 1);
		next_group->left_pipe[0] = group->right_pipe[0];
		next_group->left_pipe[1] = group->right_pipe[1];
		i++;
	}
	return (true);
}

static bool	fork_processes(t_shell *data, size_t count)
{
	size_t	i;
	pid_t	pid;
	t_group	*group;

	i = 0;
	while (i < count)
	{
		group = vec_get(&data->exec->group_vec, i);
		pid = fork();
		if (pid == -1)
			return (set_err(PERR, NULL, data));
		if (pid == 0)
		{
			if (i == 0)
				exec_process(group, LEFT);
			else if ((i == 1 && count == 2) || (count > 2 && i == count - 1))
				exec_process(group, RIGHT);
			else
				exec_process(group, MIDDLE);
		}
		else
			group->pd = pid;
		i++;
	}
	return (true);
}

/**
 * @brief Closes the pipes in the main process
 */
static bool	close_pipes(t_vector *group_vec, t_shell *data)
{
	size_t	i;
	t_group	*group;
	bool	status;

	i = 0;
	status = true;
	while (i < group_vec->length - 1)
	{
		group = vec_get(group_vec, i);
		if (group->right_pipe[0] >= 0)
			if (close(group->right_pipe[0]) == -1)
				status = set_err(PERR, NULL, data);
		if (group->right_pipe[1] >= 0)
			if (close(group->right_pipe[1]) == -1)
				status = set_err(PERR, NULL, data);
		i++;
	}
	return (status);
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
			exec_process(group, SINGLE);
	}
	else
	{
		if (!add_pipes(group_vec, group_vec->length, data))
			return (false);
		if (!fork_processes(data, group_vec->length))
			return (false);
	}
	if (!close_pipes(group_vec, data))
		return (false);
	return (true);
}
