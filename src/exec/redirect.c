/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:32:48 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/11 20:29:09 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	out_redirect(t_group *group)
{
	int		fd;
	size_t	i;
	t_token	*red_out;

	i = 0;
	while (i < vec_len(&group->out_red))
	{
		red_out = vec_get(&group->out_red, i);
		if (access(red_out->value, F_OK) == 0)
		{
			if (access(red_out->value, W_OK) == -1)
				exec_err(red_out->value, PERMISSION);
			if (red_out->type == A_REDIRECT)
				fd = open(red_out->value, O_WRONLY | O_APPEND);
			else
				fd = open(red_out->value, O_TRUNC | O_WRONLY);
		}
		else
			fd = open(red_out->value, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			exec_err(NULL, PERR);
		if (dup2(fd, STDOUT_FILENO) == -1)
			exec_err(NULL, PERR);
		i++;
	}
}

static void	in_redirect(t_group *group)
{
	size_t	i;
	t_token	*red_in;
	int		fd;

	i = 0;
	while (i < vec_len(&group->in_red))
	{
		red_in = vec_get(&group->in_red, i);
		if (access(red_in->value, F_OK) == -1)
			exec_err(red_in->value, NOT_FOUND);
		if (access(red_in->value, R_OK) == -1)
			exec_err(red_in->value, PERMISSION);
		fd = open(red_in->value, O_RDONLY);
		if (fd == -1)
			exec_err(NULL, PERR);
		if (dup2(fd, STDIN_FILENO) == -1)
			exec_err(NULL, PERR);
		i++;
	}
}

/**
 * @brief Redirects the input&output of a process
 */
void	handle_redirects(t_group *group)
{
	in_redirect(group);
	out_redirect(group);
}
