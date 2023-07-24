/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 21:42:24 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/24 11:38:21 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints an error message
 *
 * @param err The error message
 * @param cmd The command that caused the error
 * @param exit_code The exit code of the error
 */
void	err(char *err, char *cmd, int exit_code)
{
	printf("\033[1;31m");
	printf("❗️ Error: %s\n", err);
	if (cmd)
		printf("In command: %s\n", cmd);
	printf("Exit code: %d\n", exit_code);
	printf("\033[0m");
}
