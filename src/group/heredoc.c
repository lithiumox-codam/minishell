/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:15:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/19 13:51:17 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

static bool	push_hdoc(char *filename, t_group *group, t_shell *data)
{
	char	**fname;
	t_token	*red_token;

	fname = malloc(sizeof(char *));
	if (!fname)
		return (set_err(MALLOC, "push_hdoc", data));
	red_token = create_token(filename, I_REDIRECT);
	if (!red_token)
		return (free(fname), set_err(MALLOC, "push_hdoc", data));
	if (!vec_push(&group->in_red, (void *)red_token))
		return (free(fname), set_err(MALLOC, "push_hdoc", data));
	*fname = ft_strdup(filename);
	if (!*fname)
		return (free(fname), set_err(MALLOC, "push_hdoc", data));
	if (!vec_push(&data->exec->fname_vec, (void *)fname))
		return (free(*fname), free(fname), set_err(MALLOC, "push_hdoc", data));
	return (true);
}

/**
 * @brief	sets up signal handling and avoid readline catching sigs
 * @note	SIGINT = Ctrl-C
 * @note	SIGQUIT = Ctrl-\
 */
static void	setup_hdoc_signals(void)
{
	rl_catch_signals = 1;
	signal(SIGINT, signal_hdoc);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @note if signal ctrl D break while loop and return true
 */
static bool	hdoc_read(size_t heredoc_fd, t_token *token, t_shell *data)
{
	char	*line;

	setup_hdoc_signals();
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_strcmp(line, token->value) == 0)
			break ;
		if (token->type != HDOC_LITERAL)
		{
			if (!hdoc_expand(&line, data))
				return (false);
		}
		if (g_signal.inte)
			return (free(line), set_err(SIGNAL_C, NULL, data));
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	free(line);
	return (true);
}

/**
 * @param	filename the filename to be given to the new file
 * @param	token	the hdoc token
 * @note	depending on expansion DQ logic can be removed
 */
bool	heredoc(char *filename, t_token *token, t_shell *data)
{
	int	heredoc_fd;

	heredoc_fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (heredoc_fd == -1)
		return (set_err(PERR, filename, data));
	if (!hdoc_read(heredoc_fd, token, data))
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
	char	*nb;

	nb = ft_itoa(i);
	filename = ft_strjoin("./src/hdoc_files/", nb);
	free(nb);
	if (!filename)
		return (set_err(MALLOC, "hdoc_found", data));
	token = vec_get(&data->token_vec, i);
	if (!push_hdoc(filename, group, data))
		return (false);
	if (!heredoc(filename, token, data))
		return (false);
	return (true);
}
