/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 21:42:24 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/01 20:12:37 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
/**
 * @brief Prints an error message
 *
 * @param err The error message
 * @param cmd The command that caused the error
 * @param exit_code The exit code of the error

void	err(char *err, char *cmd, int exit_code)
{
	printf("\033[1;31m");
	printf("❗️ Error: %s\n", err);
	if (cmd)
		printf("In command: %s\n", cmd);
	printf("Exit code: %d\n", exit_code);
	printf("\033[0m");
}
*/

/**
 * @brief called if there is an error in minihsell that should close the program
 *
 * @param str The error message
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
	free_global(true);
	exit(exit_code);
}

/**
 * @brief Prints an error message
 *
 * @param type The type of error
 * @param name The name of the file that caused the error
 * @param func function to be called before exiting
 * @param data data to be passed to func
 * @warning func is executed with data regardless of data is NULL or not
 * @note	free global.tokens before returning?
 */
void	err(t_exit type, char *name, void (*func)(void *), void *data)
{
	int	status;

	if (func)
		func(data);
	if (type == PERROR)
	{
		perror("minishell:");
		status = errno; // related exit code?
	}
	if (type == MALLOC)
	{
		write(STDERR_FILENO, "minishell: malloc error in : ", 28);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, "\n", 1);
		status = 1;
	}
	if (type == NOT_FOUND)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		status = 127;
	}
	if (type == PERMISSION)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		status = 126;
	}
	if (type == SYNTAX)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `",
			47);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, "'\n", 2);
		status = 258;
	}
	if (type == SYNTAX_MINI)
	{
		write(STDERR_FILENO, "minishell: unfinished operator : `", 34);
		write(STDERR_FILENO, name, ft_strlen(name));
		write(STDERR_FILENO, "'\n", 2);
		status = 2;
	}
	if (type == SIGNAL_C)
	{
		write(STDERR_FILENO, "^C\n", 3);
		status = 130;
	}
	free_global(true);
	exit(status);
}
