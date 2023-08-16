/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/12 21:31:35 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

0. start cprocess
1. check for start_redirect
	if start_redirect execute start_red function
3. check for out_redirect
	if end_redirect exists end_red function
4. check for size of t_pipe
	if size==1
		dont pipe and just execute
5. if size of t_pipe size==2
	create 1 pipe, 2 cprocesses
	for each size greater than 2 add 1 pipe and 1 cprocess

make the entire executor happen in a childprocess, that way for example setting
the redirects in main process wont affect the nexg call

HEREDOCS are handled as grandchildprocesses, example:
 newfile cat << stop
1. Process < newfile in the main process.
2. Fork a child process for cat << stop.
3. In the child process, create a pipe.
4. Fork a grandchild process.
5. In the grandchild process,
	write the heredoc content to the pipe and then exit.
6. In the child process, read from the pipe and pass this as input to cat.

*/

#include <minishell.h>
