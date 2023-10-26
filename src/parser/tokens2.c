/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_vec2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:29:02 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/24 20:47:49 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Checks if a string contains an enviroment variable
 *
 * @param str The string to check
 * @return true The string contains an enviroment variable
 * @return false The string does not contain an enviroment variable
 */
bool	contains_env_var(char *str)
{
	if (str[0] == '$')
		return (true);
	return (false);
}
