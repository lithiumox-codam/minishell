/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 20:42:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/16 17:26:23 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief clears data of t_exec
 */
void	clear_exec(void *data)
{
	t_exec		*exec;
	t_vector	*p_vec;

	exec = (t_exec *)data;
	p_vec = &exec->process;
	ft_vec_free(p_vec);
}

/**
 * clears the data inside t_process;
*/
void	clear_process(void *data)
{
	t_process *p;

	p = (t_process *)data;
	ft_vec_free(&p->input);
	if (p->cmd)
		ft_free(p->cmd);
}

/**
 * @brief Create a t_exec object
 * @return t_exec* The created exec struct, NULL on failure
 */
t_exec	*create_exec(void)
{
	t_exec		*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	if (!ft_vec_init(&exec->process, 2, sizeof(t_process), clear_process))
		return (free(exec), NULL);
	exec->start_redirect = NULL;
	exec->end_redirect = NULL;
	return (exec);
}

/**
 * @brief inits a process
 * @note left/right pipe values are set to -1
 * @note pid_t is set to -2 by default, as fork() can return -1
 * @return t_process initialised, NULL on malloc failure
*/
t_process	*create_process(void)
{
	t_process	*p;
	
	p = malloc(sizeof(t_process));
	if (!p)
		return (NULL);
	if (!ft_vec_init(&p->input, 2, sizeof(t_token), clear_token))
		return (free(p), NULL);
	p->hdoc_fd = -1;
	p->cmd = NULL;
	p->pd = -2;
	p->left_pipe[0] = -1;
	p->left_pipe[1] = -1;
	p->right_pipe[0] = -1;
	p->right_pipe[1] = -1;
}
