/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 12:40:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/28 11:29:57 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	add_pipes(t_vector *group_vec, size_t process_count)
{
	size_t	i;
	t_group	*group;
	t_group	*next_group;

	i = 0;
	while (i < process_count - 1)
	{
		group = vector_get(group_vec, i);
		if (pipe(group->right_pipe) != 0)
			return (false);
		next_group = vector_get(group_vec, i + 1);
		next_group->left_pipe[0] = group->right_pipe[0];
		next_group->left_pipe[1] = group->right_pipe[1];
		i++;
	}
	return (true);
}

static bool	fork_processes(t_exec *exec, size_t process_count)
{
	size_t		i;
	t_group		*group;
	t_group		*next_group;
	t_vector	*group_vec;

	group_vec = &exec->group_vec;
	i = 0;
	while (i < process_count)
	{
		group = vector_get(group_vec, i);
		group->pd = fork();
		if (group->pd == -1)
			return (false);
		if (group->pd == 0)
		{
			if (i == 0)
				exec_process(LEFT, group, exec->envp);
			else if (i == process_count - 1)
				exec_process(RIGHT, group, exec->envp);
			else
				exec_process(MIDDLE, group, exec->envp);
		}
		i++;
	}
	return (true);
}

bool	create_processes(t_exec *exec)
{
	t_vector	*group_vec;
	size_t		process_count;
	t_group		*group;

	group_vec = &exec->group_vec;
	process_count = group_vec->length;
	if (process_count == 1)
	{
		group = vector_get(group_vec, 0);
		group->pd = fork();
		if (group->pd == -1)
			return (false);
		exec_process(SINGLE, group, exec->envp);
	}
	else
	{
		if (!add_pipes(group_vec, process_count))
			return (false);
		if (!fork_processes(group_vec, process_count))
			return (false);
	}
	return (true);
}
