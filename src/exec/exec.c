/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/07 15:40:31 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

close_pipes(t_vector *group_vec, t_shell *data)
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
				status = set_error(PERR, NULL, data);
		if (group->left_pipe[1] >= 0)
			if (close(group->left_pipe[1]) == -1)
				status = set_error(PERR, NULL, data);
		if (group->right_pipe[0] >= 0)
			if (close(group->right_pipe[0]) == -1)
				status = set_error(PERR, NULL, data);
		if (group->right_pipe[1] >= 0)
			if (close(group->right_pipe[1]) == -1)
				status = set_error(PERR, NULL, data);
		i++;
	}
	return (status);
}

/**
 * @brief	waits for processes to complete
 * @brief 	sets exit_status to the exit status of the last process to complete
 * @return	return value is true if all processes completed successfully
 * @return	if WAITPID fails, sets PERR and returns false
 */
static int	wait_processes(t_vector *group_vec, t_shell *data)
{
	size_t	i;
	t_group	*group;
	bool	success;
	int		temp;

	i = 0;
	success = true;
	while (i < group_vec->length)
	{
		group = vector_get(group_vec, i);
		if (group->pd >= 0)
			if (waitpid(group->pd, &temp, 0) == -1)
				success = false;
		i++;
	}
	if (success == true)
	{
		g_signal.exit_status = WEXITSTATUS(temp);
		return (true);
	}
	return (set_error(PERR, NULL, data));
}

/**
 * @brief	creates pipes and starts processes,
			closes pipes and waits for child_processes
 * @return	return value is the EXITSTATUS of the last childprocess to complete
	@note		sets g_signal.exit_status
 */
bool	executor(t_shell *data)
{
	t_group	*group;

	group = vec_get(&data->exec->group_vec, 0);
	if ((&data->exec->group_vec)->length == 1 && is_special_builtin(group->cmd))
	{
		exec_special_builtin(group);
		return (true);
	}
	if (!create_processes(data))
	{
		close_pipes(&data->exec->group_vec, data);
		wait_process(&data->exec->group_vec, data);
		return (false);
	}
	if (!close_pipes(&data->exec->group_vec, data))
	{
		wait_processes(&data->exec->group_vec, data);
		return (false);
	}
	if (wait_processes(&data->exec->group_vec, data) == -1)
		return (false);
	return (true);
}
