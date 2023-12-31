/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 21:42:24 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 22:33:11 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
	}
	else
		write(STDERR_FILENO, "minishell: error\n", 18);
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
	if (data->exit_type == PERR)
	{
		perror("minishell");
		data->error_type = errno;
	}
	if (data->exit_type == MALLOC)
	{
		write(STDERR_FILENO, "minishell: malloc error in : ", 30);
		write(STDERR_FILENO, data->exit_msg, ft_strlen(data->exit_msg));
		write(STDERR_FILENO, "\n", 1);
		data->error_type = CATCH_ALL;
	}
	write_err_extra(data);
	if (data->exit_type == SIGNAL_C)
		data->error_type = 130;
}

/**
 * @brief errors for inside the executable, end with exit();
 */
void	exec_err(char *str, t_exit type)
{
	if (type == PERR)
	{
		perror("minishell");
		exit(errno);
	}
	if (type == MALLOC)
	{
		write(STDERR_FILENO, "minishell: malloc error in : ", 30);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, "\n", 1);
		exit(1);
	}
	if (type == NOT_FOUND)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": command not found\n", 21);
		exit(127);
	}
	exec_err_extra(str, type);
}
