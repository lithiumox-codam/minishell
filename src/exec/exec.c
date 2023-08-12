/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/12 21:05:48 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

0. start cprocess
1. check for start_heredoc
2. check for start_redirect
	if start_redirect execute start_red function
3. check for out_redirect
4. check for size of t_pipe
	if size==1
		dont pipe and just execute
5. if size of t_pipe size==2
	create 1 pipe, 2 cprocesses
	for each size greater than 2 add 1 pipe and 1 cprocess

make the entire executor happen in a childprocess, that way for example setting
the redirects in main process wont affect the nexg call

*/

#include <minishell.h>
