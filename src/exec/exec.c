/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/04 16:39:35 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// extern t_signal	g_signal;

// close_pipes(t_vector *group_vec)
// {
// 	size_t	i;
// 	t_group	*group;
// 	bool	status;

// 	i = 0;
// 	status = true;
// 	while (i < group_vec->length)
// 	{
// 		group = vector_get(group_vec, i);
// 		if (group->left_pipe[0] >= 0)
// 			if (close(group->left_pipe[0]) == -1)
// 				status = false;
// 		if (group->left_pipe[1] >= 0)
// 			if (close(group->left_pipe[1]) == -1)
// 				status = false;
// 		if (group->right_pipe[0] >= 0)
// 			if (close(group->right_pipe[0]) == -1)
// 				status = false;
// 		if (group->right_pipe[1] >= 0)
// 			if (close(group->right_pipe[1]) == -1)
// 				status = false;
// 		i++;
// 	}
// 	return (status);
// }

// static int	wait_processes(t_vector *group_vec)
// {
// 	size_t	i;
// 	t_group	*group;
// 	bool	success;
// 	int		temp;

// 	i = 0;
// 	success = true;
// 	while (i < group_vec->length)
// 	{
// 		group = vector_get(group_vec, i);
// 		if (group->pd >= 0)
// 			if (waitpid(group->pd, &temp, 0) == -1)
// 				success = false;
// 		i++;
// 	}
// 	if (success == true)
// 	{
// 		g_signal.exit_status = WEXITSTATUS(temp);
// 		return (true);
// 	}
// 	return (success);
// }

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
	// if (!create_processes(data))
	// {
	// 	close_pipes(&data->exec->group_vec);
	// 	wait_process(&data->exec->group_vec);
	// 	return (set_err(PERR, NULL, data));
	// }
	// if (!close_pipes(&data->exec->group_vec))
	// {
	// 	wait_processes(&data->exec->group_vec);
	// 	return (set_err(PERR, NULL, data));
	// }
	// if (wait_processes(&data->exec->group_vec) == -1)
	// 	return (set_err(PERR, NULL, data));
	return (true);
}
