/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:15:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 20:36:35 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	loop(int heredoc_fd, char *stop, t_types type, t_shell *data)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, stop) == 0)
			break ;
		if (type == STRING)
		{
			line = expand_line(line);
			if (!line)
			{
				free(line);
				err(MALLOC, "hdoc_loop", data, true);
			}
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	free(line);
}

/**
 * @param	filename the filename to be given to the new file
 * @param	stop	the string to stop readline
 * @param	type	string or quoted, if quoted there will be no expansion.
 * @param	exec	to be freed when an error occurs
 */
void	heredoc(char *filename, char *stop, t_types type, t_shell *data)
{
	int	heredoc_fd;

	heredoc_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (heredoc_fd == -1)
		err(PERROR, filename, data, true);
	if (heredoc_fd < 0)
		return (false);
	close(heredoc_fd);
	return (true);
}
