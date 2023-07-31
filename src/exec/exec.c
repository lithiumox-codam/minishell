/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/31 20:02:35 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

1. begin indirect
2. end outdirect
3. count pipes

pipe_count

put all structs in vector

each process pipes and forks
left_process 1 pipe
middle_process a pipe from left_process and a pipe_right


if (pipe_count > 0)
{
	left_process;
	while (pipe_count > 1)
	{
		middle_process.c
		pipe_count--;
	}
	right_process;
}
vec->length
waitpid's 
close_pipes

*/

#include <minishell.h>







