/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/16 12:15:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/16 17:21:14 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*


int	ft_heredoc(char *stop, t_process, int quotes)

Create newfile with open(); 0_CREATE

use readline --> interpet based on quotes
write(heredoc_fd)


dup2(fd_replace, heredoc_Fd)

close(herredoc_fd);
remove the file? --> or remove later in child_process;

*/