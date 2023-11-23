/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_extra.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/22 22:29:17 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/23 14:08:40 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exec_err_cmd(char *str, t_exit type)
{
	if (type == NO_SUCH_CMD)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": command not found\n", 21);
		exit(127);
	}
	if (type == PERMISSION_CMD)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": Permission denied\n", 21);
		exit(126);
	}
}

/**
 * @info NO_SUCH is volgens de tester 1 niet 126
 */
void	exec_err_extra(char *str, t_exit type)
{
	if (type == PERMISSION)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": Permission denied\n", 21);
		exit(1);
	}
	if (type == NO_SUCH)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		exit(1);
	}
	if (type == IS_DIRECT)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": Is a directory\n", 18);
		exit(126);
	}
	exec_err_cmd(str, type);
}

void	write_err_extra(t_shell *data)
{
	if (data->exit_type == SYNTAX)
	{
		write(2, "minishell: syntax error near unexpected token `", 48);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, "'\n", 2);
		data->error_type = SYNTAX_ERROR;
	}
	if (data->exit_type == SYNTAX_MINI)
	{
		write(STDERR_FILENO, "minishell: syntax error: unfinished quote\n", 43);
		data->error_type = 2;
	}
	if (data->exit_type == OUT_OF_SCOPE)
	{
		write(2, "minishell: operators: () ; \\ & ||: out of scope\n", 49);
		data->error_type = 2;
	}
}
