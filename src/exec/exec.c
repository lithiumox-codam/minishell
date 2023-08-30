/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/31 00:37:39 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	close_pipes(t_vector *group_vec)
{
	size_t	i;
	t_group	*group;
	bool	status;

	i = 0;
	status = true;
	while (i < group_vec->length)
	{
		group = vector_get(group_vec, i);
		if (group->left_pipe[0] >= 0)
			if (close(group->left_pipe[0]) == -1)
				status = false;
		if (group->left_pipe[1] >= 0)
			if (close(group->left_pipe[1]) == -1)
				status = false;
		if (group->right_pipe[0] >= 0)
			if (close(group->right_pipe[0]) == -1)
				status = false;
		if (group->right_pipe[1] >= 0)
			if (close(group->right_pipe[1]) == -1)
				status = false;
		i++;
	}
	return (status);
}

static int	wait_processes(t_vector *group_vec)
{
	size_t	i;
	t_group	*group;
	int		status;
	int		temp;

	i = 0;
	status = 0;
	while (i < group_vec->length)
	{
		group = vector_get(group_vec, i);
		if (group->pd >= 0)
			if (waitpid(group->pd, &temp, 0) == -1)
				status = -1;
		i++;
	}
	if (status == 0)
		status = WEXITSTATUS(temp);
	return (status);
}

bool	executor(t_exec *exec)
{
	int	temp;
	int	status;

	if (!create_processes(exec))
	{
		close_pipes(&exec->group_vec);
		wait_process(&exec->group_vec);
		err(PERROR, NULL, clear_exec, exec);
	}
	if (!close_pipes(&exec->group_vec))
	{
		wait_processes(&exec->group_vec);
		err(PERROR, NULL, clear_exec, exec);
	}
	status = wait_processes(&exec->group_vec);
	if (!status)
		err(PERROR, NULL, clear_exec, exec);
	clear_exec(exec);
	exit(status);
}
