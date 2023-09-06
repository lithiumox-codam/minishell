/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 21:42:24 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 18:36:43 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	signal;

/**
 * @brief called if there is an error in minihsell that should close the program
 *
 * @param str The error message
 * @param int the exit code to be set
 * @param data the t_shell data to freed
 */
void	exit_mini(char *str, int exit_code)
{
	if (str)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
	}
	else
		write(STDERR_FILENO, "minishell: error\n", 16);
	exit(exit_code);
}

/**
 * @brief Prints an error message
 *
 * @param type The type of error
 * @param name The name of the file that caused the error
 * @param data t_shell data to be freed
 * @param free_struct if t_shell should be freed including env
 */
void	err(t_exit type, char *name, t_shell *data, bool free_struct)
{
	if (type == PERROR)
	{
		perror("minishell:");
		signal.exit_status = errno;
	}
	if (type == MALLOC)
	{
		write(STDERR_FILENO, "minishell: malloc error in : ", 28);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, "\n", 1);
		signal.exit_status = 1;
	}
	if (type == NOT_FOUND)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		signal.exit_status = 127;
	}
	if (type == PERMISSION)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		signal.exit_status = 126;
	}
	if (type == SYNTAX)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `",
			47);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, "'\n", 2);
		signal.exit_status = 258;
	}
	if (type == SYNTAX_MINI)
	{
		write(STDERR_FILENO, "minishell: unfinished operator : `", 34);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, "'\n", 2);
		signal.exit_status = 2;
	}
	if (type == SIGNAL_C)
	{
		write(STDERR_FILENO, "^C\n", 3);
		signal.exit_status = 130;
	}
	free_shell(data, free_struct);
	exit(signal.exit_status);
}
