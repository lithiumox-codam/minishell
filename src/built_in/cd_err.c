/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_err.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/22 17:42:21 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 21:37:32 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints an error message based on the type of error
 * @details If the type is GOOD, nothing is printed
 * @details the t_Signal exit_status is set to the correct value
 *
 * @param data	general data struct
 */
void	write_err_cd(t_shell *data, size_t option, char *path, char *extra)
{
	if (option)
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 29);
		data->error_type = CATCH_ALL;
	}
	else if (option == 2)
	{
		write(2, "minishell: cd: ", 15);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, extra, ft_strlen(extra));
		write(2, "\n", 1);
		data->error_type = CATCH_ALL;
	}
}
