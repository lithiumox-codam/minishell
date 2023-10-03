/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:15:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/03 18:08:05 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	push_hdoc(char *filename, t_group *group, t_shell *data)
{
	char	*fname;
	t_token	*red_token;

	fname = ft_strdup(filename);
	if (!fname)
		return (set_err(MALLOC, "push_hdoc", data));
	red_token = create_token(filename, I_REDIRECT);
	if (!red_token)
		return (set_err(MALLOC, "push_hdoc", data));
	if (!vec_push(&group->in_red, (void *)red_token))
		return (set_err(MALLOC, "push_hdoc", data));
	if (!vec_push(&data->exec->fname_vec, (void *)fname))
		return (set_err(MALLOC, "push_hdoc", data));
	return (true);
}

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
			// ^^^^ this is placeholder to avoid data error
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
 * @param	type	string or quoted, if quoted there will be no expansion.
 * @param	exec	to be freed when an error occurs
 */
bool	heredoc(char *filename, char *stop, bool expand, t_shell *data)
{
	int	heredoc_fd;

	heredoc_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (heredoc_fd == -1)
		return (set_err(PERR, filename, data));
	if (!loop(heredoc_fd, stop, expand, data))
	{
		close(heredoc_fd);
		return (false);
	}
	if (!close(heredoc_fd))
		return (set_err(PERR, filename, data));
	return (true);
}

/**
 * @brief Creates a token for the hdoc file, and adds the filename to the f_name
 * @param	group the group to add the new token_vec to
 * @param	i to step over the heredoc and the quotes / filenames
 * @param	data general data struct
 * @param
 */
bool	hdoc_found(t_group *group, size_t i, t_shell *data)
{
	t_token	*token;
	t_token	*stop;
	bool	succes;
	char	*filename;

	filename = ft_strjoin("./src/.heredoc/", ft_itoa((i)));
	if (!filename)
		return (set_err(MALLOC, "hdoc_found", data));
	token = vec_get(&data->token_vec, i);
	if ((is_encased_dq(token->value)) && ft_strlen(token->value) == 2)
		succes = heredoc(filename, "", true, data);
	else
	{
		stop = rm_quotes(token, true);
		if (!stop)
			return (set_err(MALLOC, "hdoc_found", data));
		succes = heredoc(filename, stop->value, is_encased_dq(token), data);
		clear_token(stop);
	}
	if (!succes)
		return (false);
	return (push_hdoc(filename, group, data));
}
