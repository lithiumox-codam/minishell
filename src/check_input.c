/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/14 14:50:16 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/15 15:18:46 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_next(char *str, char quote, char other)
{
	int		i;

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

static char	*parentheses(char *str)
{
	str++;
	while (*str)
	{
		if (*str == ')')
			return (str);
		else
		{
			if (*str == '(')
				str = parentheses(str);
			else if (*str == '\"')
				str = find_next(str, '\"', '\'');
			else if (*str == '\'')
				str = find_next(str, '\'', '\"');
			if (!str)
				return (NULL);
		}
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
	char	*paranthese_error;
	char	*error;

	paranthese_error = "minishell: syntax error near unexpected token `)'\n";
	error = "minishell: syntax error: unfinished quote or parantheses\n";
	if (!input)
		return (false);
	while (*input)
	{
		if (*input == ')')
			return (write(2, paranthese_error, 50), false);
		else
		{
			if (*input == '(')
				input = parentheses(input);
			else if (*input == '\"')
				input = find_next(input, '\"', '\'');
			else if (*input == '\'')
				input = find_next(input, '\'', '\"');
			if (!input)
				return (write(2, error, 57), false);
		}
		input++;
	}
	return (true);
}

/**
 * @brief	checks if both strings are exactly equal
 * @return	true if strings are equal, false if strings are not equal
*/
bool	mini_strcmp(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (false);
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (false);
	return (true);
}
