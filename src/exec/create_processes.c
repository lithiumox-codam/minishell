/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_processes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 12:40:07 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/07 15:25:54 by mdekker/jde   ########   odam.nl         */
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
		group = vector_get(group_vec, i);
		if (pipe(group->right_pipe) != 0)
			return (set_err(PERR, NULL, data));
		next_group = vector_get(group_vec, i + 1);
		next_group->left_pipe[0] = group->right_pipe[0];
		next_group->left_pipe[1] = group->right_pipe[1];
		i++;
	}
	return (true);
}

static bool	fork_processes(t_shell *data, size_t process_count)
{
	size_t		i;
	t_group		*group;
	t_group		*next_group;
	t_vector	*group_vec;

	group_vec = &data->exec->group_vec;
	i = 0;
	while (i < process_count)
	{
		group = vector_get(group_vec, i);
		group->pd = fork();
		if (group->pd == -1)
			return (set_err(PERR, NULL, data));
		if (group->pd == 0)
		{
			if (i == 0)
				exec_process(LEFT, group);
			else if (i == process_count - 1)
				exec_process(RIGHT, group);
			else
				exec_process(MIDDLE, group);
		}
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
		group = vector_get(group_vec, 0);
		group->pd = fork();
		if (group->pd == -1)
			return (set_err(PERR, NULL, data));
		exec_process(SINGLE, group);
	}
	else
	{
		if (!add_pipes(group_vec, group_vec->length, data))
			return (false);
		if (!fork_processes(data, group_vec->length))
			return (false);
	}
	return (true);
}
