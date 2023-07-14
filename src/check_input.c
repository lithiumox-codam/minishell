/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 14:50:16 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/14 14:55:07 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_next(char *str, char quote, char other)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	str++;
	while (*str != '\0' && *str != quote)
	{
		if (*str == other)
			i++;
		str++;
	}
	if (*str == '\0')
		return (NULL);
	if (i % 2 != 0)
		return (NULL);
	return (str);
}

char	*parentheses(char *str)
{
	if (!str)
		return (NULL);
	str++;
	while (*str)
	{
		if (*str == '\"')
		{
			str = find_next(str++, '\"', '\'');
			if (!str)
				return (NULL);
		}
		if (*str == '\'')
		{
			str = find_next(str++, '\'', '\"');
			if (!str)
				return (NULL);
		}
		if (*str == ')')
			return (str);
		str++;
	}
	return (NULL);
}

/**
 * @brief	function checks for unfinished quotes or parantheses
 * @param	input string to check
 * @return	true if string is good, false if quote or parantheses is unfinished
*/
bool	check_quotes_parantheses(char *input)
{
	if (!input)
		return (false);
	while (*input)
	{
		if (*input == '(')
		{
			input = parentheses(input++);
			if (!input)
				return (false);
		}
		else if (*input == '\"')
		{
			input = find_next(input, '\"', '\'');
			if (!input)
				return (false);
		}
		else if (*input == '\'')
		{
			input = find_next(input++, '\'', '\"');
			if (!input)
				return (false);
		}
		input++;
	}
	return (true);
}
