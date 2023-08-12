/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:50 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/11 12:12:25 by mdekker/jde   ########   odam.nl         */
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


for each struct in commands t_exec{
	// Create a pipe
	int pipefd[2];
	pipe(pipefd);

	// Fork a new child process
	pid_t pid = fork();


	if (pid == 0) { // Child process
	if (is_middle_process) {
		// Close the unused write end of the input pipe
		close(input_pipe[1]);

		// Redirect standard input to the read end of the input pipe
		dup2(input_pipe[0], STDIN_FILENO);
		close(input_pipe[0]);

		// Close the unused read end of the output pipe
		close(output_pipe[0]);

		// Redirect standard output to the write end of the output pipe
		dup2(output_pipe[1], STDOUT_FILENO);
		close(output_pipe[1]);
	}

	// Execute the command
	execvp(command, command_args);

	if (pid == 0) { // Child process
		iif left_pipe[0] == -1 && right_pipe[0] != -1
			left_process
		iif left_pipe[0] != -1 && right_pipe[0] == -1
			right_process
		if left_pipe[0] != -1 && right_pipe[0] != -1
			middle_process

		close(pipefd[0]);

		// Redirect standard output to the write end of the pipe
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		// Execute the command
		execvp(command, command_args);
	} else { // Parent process
		// Close the write end of the pipe
		close(pipefd[1]);

		// Redirect standard input to the read end of the pipe
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}


make the entire executor happen in a childprocess, that way for example setting
the redirects in main process wont affect the nexg call

*/

#include <minishell.h>
