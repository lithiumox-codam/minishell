/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 20:42:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/04 05:28:20 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Create a t_exec object
 * @param cmd is assigned to exec->cmd
 * @return t_exec* The created exec struct
 * @note left/right pipe values are set to -1
 * @note pid_t is set to -2 by default, as fork() can return -1
 */
t_exec	*create_exec(char **cmd)
{
	t_exec	*exec;

	exec = malloc(sizeof(exec));
	if (!exec)
		return (NULL);
	exec->cmd = cmd;
	exec->pd = -2;
	exec->locate = 0;
	exec->left_pipe[0] = -1;
	exec->left_pipe[1] = -1;
	exec->right_pipe[0] = -1;
	exec->right_pipe[1] = -1;
	return (exec);
}

/**
 * @brief clears data of t_exec
 */
void	clear_exec(void *data)
{
	t_exec	*exec;

	exec = (t_exec *)data;
	ft_free(exec->cmd);
}
