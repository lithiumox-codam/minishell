/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 21:42:24 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/07 13:16:30 by mdekker/jde   ########   odam.nl         */
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

bool	set_err(t_exit type, char *msg, t_shell *data)
{
	if (type == GOOD)
		return (true);
	data->exit_type = type;
	data->exit_msg = msg;
	return (false);
}

/**
 * @brief Prints an error message based on the type of error
 * @details If the type is GOOD, nothing is printed
 * @details the t_Signal exit_status is set to the correct value
 *
 * @param data	general data struct
 */
void	write_err(t_shell *data)
{
	if (data->exit_type == GOOD)
		return ;
	if (data->exit_type == PERROR)
	{
		perror("minishell:");
		signal.exit_status = errno;
	}
	if (data->exit_type == MALLOC)
	{
		write(STDERR_FILENO, "minishell: malloc error in : ", 28);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, "\n", 1);
		signal.exit_status = 1;
	}
	if (data->exit_type == NOT_FOUND)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		signal.exit_status = 127;
	}
	if (data->exit_type == PERMISSION)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		signal.exit_status = 126;
	}
	if (data->exit_type == SYNTAX)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `",
			47);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, "'\n", 2);
		signal.exit_status = 258;
	}
	if (data->exit_type == SYNTAX_MINI)
	{
		write(STDERR_FILENO, "minishell: unfinished operator : `", 34);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, "'\n", 2);
		signal.exit_status = 2;
	}
	if (data->exit_type == SIGNAL_C)
	{
		write(STDERR_FILENO, "^C\n", 3);
		signal.exit_status = 130;
	}
	free_shell(data, false);
}
