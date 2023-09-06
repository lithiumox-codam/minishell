/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 20:49:39 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

close_pipes(t_vector *group_vec)
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

static void	check_for_exit(t_shell *data)
{
	printf("exit was called\n");
	// int long long atoi
	free_shell(data, true);
	exit(10);
}

/**
 * @brief	creates pipes and starts processes,
		closes pipes and waits for child_processes
 * @return	return value is the EXITSTATUS of the last childprocess to complete

	* @note if all testing is succesful make it a void function and exit status instead of returning it
 */
int	executor(t_shell *data)
{
	int	temp;
	int	status;

	if ((&data->exec->group_vec)->length == 1)
	{
		check_for_exit(data); // write function to exit()
	}
	if (!create_processes(data))
	{
		close_pipes(&data->exec->group_vec);
		wait_process(&data->exec->group_vec);
		err(PERROR, NULL, data, true);
	}
	if (!close_pipes(&data->exec->group_vec))
	{
		wait_processes(&data->exec->group_vec);
		err(PERROR, NULL, data, true);
	}
	status = wait_processes(&data->exec->group_vec);
	if (status == -1)
		err(PERROR, NULL, data, true);
	return (status);
}
