/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 11:37:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 04:34:01 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Checks if a string is encased in double quotes
 *
 * @param str The string to check
 * @return true The string is encased in double quotes
 * @return false The string is not encased in double quotes
 */
bool	is_encased_dq(char *str)
{
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		return (true);
	return (false);
}

/**
 * @brief Checks if a string is encased in single quotes
 *
 * @param str The string to check
 * @return true The string is encased in single quotes
 * @return false The string is not encased in single quotes
 */
bool	is_encased_sq(char *str)
{
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (true);
	return (false);
}

/**
 * @brief Checks if a string is encased in parentheses
 *
 * @param str The string to check
 * @return true The string is encased in parentheses
 * @return false The string is not encased in parentheses
 */
bool	is_encased_parentheses(char *str)
{
	if (str[0] == '(' && str[ft_strlen(str) - 1] == ')')
		return (true);
	return (false);
}
