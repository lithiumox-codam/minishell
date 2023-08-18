/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/18 14:36:30 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

0. start cprocess
4. check for size of t_pipe
	if size==1
		dont pipe and call single_process
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

bool	exec(t_exec *exec)
{
	{
		size_t len = exec->group_vec->length;
		size_t i = 0;
		t_group *group;

		while (i < len)
		{
			group = vector_get(exec->group_vec, i);
			group->pd = fork();
			if (group->pd == 0)
			{
				if (len == 1)
				{
					single_process(group);
				}
				else if (len == 2)
				{
					if (i == 0)
					{
						pipe(group->right_pipe);
						left_process(group);
					}
					else
					{
						pipe(group->left_pipe);
						right_process(group);
					}
				}
				else
				{
					if (i == 0)
					{
						pipe(group->right_pipe);
						left_process(group);
					}
					else if (i == len - 1)
					{
						pipe(group->left_pipe);
						right_process(group);
					}
					else
					{
						pipe(group->left_pipe);
						pipe(group->right_pipe);
						middle_process(group);
					}
				}
				exit(0);
			}
			i++;
		}

		i = 0;
		while (i < len)
		{
			group = vector_get(exec->group_vec, i);
			waitpid(group->pd, NULL, 0);
			i++;
		}
		return (true);
	}
