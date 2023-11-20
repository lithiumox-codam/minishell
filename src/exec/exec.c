/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/20 17:43:12 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief	waits for processes to complete
 * @brief 	sets exit_status to the exit status of the last process to complete
 * @return	return value is true if all processes completed successfully
 * @return	if WAITPID fails, sets PERR and returns false
 */
static int	wait_processes(t_vector *group_vec, t_shell *data,
		bool check_status)
{
	size_t	i;
	t_group	*group;
	bool	success;
	int		temp;

	success = true;
	i = 0;
	while (i < group_vec->length)
	{
		group = vec_get(group_vec, i);
		if (group->pd >= 0)
			if (waitpid(group->pd, &temp, 0) == -1)
				success = false;
		i++;
	}
	if (check_status)
	{
		if (success == true)
		{
			data->error_type = WEXITSTATUS(temp);
			return (true);
		}
		return (set_err(PERR, NULL, data));
	}
	return (false);
}

/**
 * @brief	creates pipes and starts processes,
 * closes pipes and waits for child_processes
 * @return	return value is the EXITSTATUS of the last childprocess to complete
 * @note	sets the data error_type
 */
bool	executor(t_shell *data)
{
	t_group	*group;

	group = vec_get(&data->exec->group_vec, 0);
	if ((&data->exec->group_vec)->length == 1 && is_special_builtin(group->cmd))
	{
		exec_special_builtin(group, data);
		return (true);
	}
	else
	{
		if (!create_processes(data))
		{
			wait_processes(&data->exec->group_vec, data, false);
			return (false);
		}
		if (wait_processes(&data->exec->group_vec, data, true) == -1)
			return (false);
	}
	return (true);
}
