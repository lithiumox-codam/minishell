/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:15:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/23 20:09:15 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	push_hdoc(char *filename, t_group *group, t_shell *data)
{
	char	*fname;
	t_token	*fname_token;
	t_token	*red_token;

	fname = ft_strdup(filename);
	if (!fname)
		return (set_err(MALLOC, "push_hdoc", data));
	red_token = create_token(filename, I_REDIRECT);
	if (!red_token)
		return (set_err(MALLOC, "push_hdoc", data));
	if (!vec_push(&group->in_red, (void *)red_token))
		return (set_err(MALLOC, "push_hdoc", data));
	fname_token = create_token(fname, STRING);
	if (!fname_token)
		return (set_err(MALLOC, "push_hdoc", data));
	if (!vec_push(&data->exec->fname_vec, (void *)fname_token))
		return (set_err(MALLOC, "push_hdoc", data));
	return (true);
}

/**
 * @note if signal ctrl D break while loop and return true
 */
static bool	loop(size_t heredoc_fd, char *stop, bool expand, t_shell *data)
{
	char	*line;

	// char	*expanded_line;
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, stop) == 0)
			break ;
		if (expand)
		{
			// expanded_line = expand(line);
			// free(line);
			// if (!expanded_line)
			// 	return (set_err(MALLOC, "loop", data));
			// line = expanded_line;
			if (!data)
				return (false);
			// ^^^^ this is placeholder to avoid data unused error
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	free(line);
	return (true);
}

/**
 * @param	filename the filename to be given to the new file
 * @param	stop	the string to stop readline
 * @note	depending on expansion DQ logic can be removed
 */
bool	heredoc(char *filename, char *stop, t_shell *data)
{
	int		heredoc_fd;
	bool	loop_success;

	heredoc_fd = open(filename, O_CREAT | O_RDWR, 0644);
	if (heredoc_fd == -1)
		return (set_err(PERR, filename, data));
	if ((is_encased_dq(stop)) && ft_strlen(stop) == 2)
		loop_success = loop(heredoc_fd, "", true, data);
	else if (is_encased_dq(stop))
	{
		stop = ft_strtrim(stop, "\"");
		if (!stop)
			return (set_err(MALLOC, "heredoc", data));
		loop_success = loop(heredoc_fd, stop, true, data);
	}
	else
		loop_success = loop(heredoc_fd, stop, false, data);
	if (!loop_success)
		return (close(heredoc_fd), false);
	if (close(heredoc_fd) != 0)
		return (set_err(PERR, filename, data));
	return (true);
}

/**
 * @brief 	creates a heredoc file and adds it to the group
 * @param	group the group to add the new token_vec to
 * @param	i to step over the heredoc and the quotes / filenames
 * @param	data general data struct
 * @param
 */
bool	hdoc_found(t_group *group, size_t i, t_shell *data)
{
	t_token	*token;
	char	*filename;

	filename = ft_strjoin("./src/hdoc_files/", ft_itoa((i)));
	if (!filename)
		return (set_err(MALLOC, "hdoc_found", data));
	token = vec_get(&data->token_vec, i);
	if (!heredoc(filename, token->value, data))
		return (false);
	return (push_hdoc(filename, group, data));
}
