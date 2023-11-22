/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 14:50:46 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/21 17:14:11 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Checks if a string contains a PIPE
 *
 * @param str The string to check
 * @return true The string contains a PIPE
 * @return false The string does not contain a PIPE
 */
bool	is_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if a string contains a REDIRECT
 *
 * @param str The string to check
 * @return true The string contains a REDIRECT
 * @return false The string does not contain a REDIRECT
 */
bool	is_r_redirect(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if a string contains a REDIRECT
 *
 * @param str The string to check
 * @return true The string contains a REDIRECT
 * @return false The string does not contain a REDIRECT
 */
bool	is_l_redirect(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if a string contains a HEREDOC
 *
 * @param str The string to check
 * @return true The string contains a HEREDOC
 * @return false The string does not contain a HEREDOC
 */
bool	is_a_redirect(char *str)
{
	if (ft_strcmp(str, ">>") == 0)
		return (true);
	return (false);
}

/**
 * @brief Checks if a string contains a HEREDOC
 *
 * @param str The string to check
 * @return true The string contains a HEREDOC
 * @return false The string does not contain a HEREDOC
 */
bool	is_heredoc(char *str)
{
	if (ft_strcmp(str, "<<") == 0)
		return (true);
	return (false);
}
