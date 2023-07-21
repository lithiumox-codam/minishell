/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 16:29:02 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 19:48:27 by mdekker/jde   ########   odam.nl         */
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

/**
 * @brief Checks if a string contains an AND
 *
 * @param str The string to check
 * @return true The string contains an AND
 * @return false The string does not contain an AND
 */
bool	is_and(char *str)
{
	if (ft_strcmp(str, "&&") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if a string contains an OR
 *
 * @param str The string to check
 * @return true The string contains an OR
 * @return false The string does not contain an OR
 */
bool	is_or(char *str)
{
	if (ft_strcmp(str, "||") == 0)
		return (true);
	return (false);
}
