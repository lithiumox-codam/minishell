/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:15:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/18 14:09:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*

Expansion na heredoc
bash-3.2$ cat << $USER
> hello
> juliusdebaaij
> $USER
hello
juliusdebaaij
bash-3.2$ cat $USER
cat: juliusdebaaij: No such file or directory

*/
/*


int	ft_heredoc(char *filename, char *stop, t_type quotes)


if t_type quotes == NULL

Create newfile with open(); 0_CREATE

use readline --> interpet based on quotes
write(heredoc_fd)
close(herredoc_fd);
remove the file? --> or remove later in child_process;

*/

bool	heredoc(char *filename, char *stop, t_type type)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open(filename, O_CREAT | O_WRONLY, 0644);
	if (heredoc_fd < 0)
		return (false);
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, stop) == 0)
			break ;
		if (type == STRING)
		{
			line = expand_line(line);
			if (!line)
				return (false);
		}
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	close(heredoc_fd);
	return (true);
}
