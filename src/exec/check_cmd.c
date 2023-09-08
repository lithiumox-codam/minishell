/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 17:36:19 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/01 19:44:26 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void check_cmd(char *str)
// {
// 	if (cmd[0] == '\0')
// 		cmd_error("", data);
// 	if (cmd[0] == ' ')
// 		cmd_error(cmd, data);
// 	if (0 == access(cmd, F_OK) && 0 != access(cmd, X_OK))
// 		permission_error(cmd, 126, data);
// 	if (0 == access(cmd, F_OK | X_OK))
// 		absolute_cmd(data, cmd);
// 	else
// 	{
// 		if (0 != find_path(data, envp))
// 			path_error(cmd, data);
// 		if (0 != find_cmd(data, cmd))
// 			cmd_error(cmd, data);
// 	}
// }

