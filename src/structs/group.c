/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 20:42:59 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 18:49:48 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * clears the data inside t_process;
 */
void	clear_group(void *data)
{
	t_group	*p;

	if (!data)
		return ;
	p = (t_group *)data;
	vec_free(&p->input);
	if (p->cmd)
		ft_free(p->cmd);
	p = NULL;
}

void	clear_fname(void *data)
{
	char	*filename;

	if (!data)
		return ;
	filename = (char *)data;
	if (-1 == unlink(filename))
		perror("minishell:");
	free(filename);
	filename = NULL;
}

void	clear_exec(t_exec *exec)
{
	if (!exec)
		return ;
	vec_free(&exec->group_vec);
	vec_free(&exec->fname_vec);
	free(exec);
	exec = NULL;
}

/**
 * @brief init a t_group object
 * @note left/right pipe values are set to -1
 * @note pid_t is set to -2 by default
 * @return t_group initialised, NULL on malloc failure
 */
t_group	*create_group(void)
{
	t_group	*p;

	p = malloc(sizeof(t_group));
	if (!p)
		return (NULL);
	if (!vec_init(&p->input, 2, sizeof(t_token), clear_token))
		return (free(p), NULL);
	p->cmd = NULL;
	p->pd = -2;
	p->left_pipe[0] = -1;
	p->left_pipe[1] = -1;
	p->right_pipe[0] = -1;
	p->right_pipe[1] = -1;
}

/**
 * @brief creates t_exec
 */
t_exec	*create_exec(void)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	if (!vec_init(&exec->group_vec, 2, sizeof(t_group), clear_group))
	{
		free(exec);
		return (NULL);
	}
	if (!vec_init(&exec->fname_vec, 1, sizeof(char *), clear_fname))
	{
		vec_free(&exec->group_vec);
		free(exec);
		return (NULL);
	}
	return (exec);
}
