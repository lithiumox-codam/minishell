/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:32:48 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 16:13:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef struct s_local_fd
{
	int		in_fd;
	int		out_fd;
	int		*fds;
	int		count;
}			t_fds;

static void	set_out_redirect(t_token *token, t_fds *fds)
{
	int	fd;

	if (access(token->value, F_OK) == 0)
	{
		if (token->type == A_REDIRECT)
			fd = open(token->value, O_WRONLY | O_APPEND);
		else
			fd = open(token->value, O_TRUNC | O_WRONLY);
	}
	else
		fd = open(token->value, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		exec_err(NULL, PERR);
	(*fds).out_fd = fd;
	(*fds).fds[(*fds).count] = fd;
	(*fds).count++;
}

void	set_in_redirect(t_token *token, t_fds *fds)
{
	int	fd;

	fd = open(token->value, O_RDONLY);
	if (fd == -1)
		exec_err(NULL, PERR);
	(*fds).in_fd = fd;
	(*fds).fds[(*fds).count] = fd;
	(*fds).count++;
}

void	validate_redirect(t_token *token)
{
	if (token->type == I_REDIRECT)
	{
		if (access(token->value, F_OK) == -1)
			exec_err(token->value, NO_SUCH);
		if (access(token->value, R_OK) == -1)
			exec_err(token->value, PERMISSION);
	}
	else if (access(token->value, F_OK) == 0)
	{
		if (access(token->value, W_OK) == -1)
			exec_err(token->value, PERMISSION);
	}
}

void	close_fds(t_fds *fds)
{
	int	i;

	i = 0;
	while (i < fds->count)
	{
		if (fds->fds[i] != fds->in_fd && fds->fds[i] != fds->out_fd)
			if (close(fds->fds[i]) == -1)
				exec_err(NULL, PERR);
		i++;
	}
	free(fds->fds);
}

/**
 * @brief Redirects the input&output of a process
 */
void	handle_redirects(t_group *group)
{
	size_t	i;
	t_token	*token;
	t_fds	fds;

	if (group->redirects.length == 0)
		return ;
	fds.fds = malloc(sizeof(int) * (&group->redirects)->length);
	if (!fds.fds)
		exec_err(NULL, MALLOC);
	fds.count = 0;
	fds.in_fd = -1;
	fds.out_fd = -1;
	i = 0;
	while (i < (&group->redirects)->length)
	{
		token = vec_get(&group->redirects, i);
		validate_redirect(token);
		if (token->type == I_REDIRECT)
			set_in_redirect(token, &fds);
		else
			set_out_redirect(token, &fds);
		i++;
	}
	group->in_red = fds.in_fd;
	group->out_red = fds.out_fd;
	close_fds(&fds);
}
