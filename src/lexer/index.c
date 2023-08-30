/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:32:55 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/30 22:02:44 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Checks if the next quote is valid
 *
 * @param str The string to check
 * @param i The index of the string to check
 * @return true The next quote is valid
 * @return false The next quote is not valid
 */
static bool	check_next_quote(char *str, size_t *i)
{
	char	quote;

	quote = str[(*i)];
	(*i)++;
	while (str[(*i)] != '\0' && str[(*i)] != quote)
		(*i)++;
	if (str[(*i)] == '\0')
		return (false);
	(*i)++;
	return (true);
}

/**
 * @brief Checks if the parantheses are valid
 *
 * @param str The string to check
 * @param i The index of the string to check
 * @return true The parantheses are valid
 * @return false The parantheses are not valid
 */
static bool	check_parantheses(char *str, size_t *i)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != ')')
	{
		if (str[*i] == '(')
		{
			if (!check_parantheses(str, i))
				return (false);
		}
		else if (str[*i] == '\"' || str[*i] == '\'')
		{
			if (!check_next_quote(str, i))
				return (false);
		}
		else
			(*i)++;
	}
	if (str[*i] == '\0')
		return (false);
	(*i)++;
	return (true);
}

/**
 * @brief Checks if the delimiters are valid
 *
 * @param str The string to check
 * @return true The delimiters are valid
 * @return false The delimiters are not valid
 */
static bool	check_delimiters(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
	{
		if (!check_next_quote(str, &i))
			return (false);
	}
	else if (str[i] == ')')
		return (false);
	else if (str[i] == '(')
	{
		if (!check_parantheses(str, &i))
			return (false);
	}
	return (true);
}

/**
 * @brief Creates a string from another string
 *
 * @param str The string to create a string from
 * @param i The index of the string to create
 * @param vec The vector to store the string in
 * @return true The string was succesfully stored
 * @return false The string could not be stored
 */
bool	make_string(char *str, size_t *i, t_vector *vec)
{
	if (str[*i] == '\"' || str[*i] == '\'')
	{
		if (!create_quote_string(str, i, vec))
			return (false);
	}
	else if (str[*i] == '(')
	{
		if (!create_paran_string(str, i, vec))
			return (false);
	}
	return (true);
}

/**
 * @brief Splits a string into tokens
 *
 * @param input	The string to split
 * @param vec The vector to store the tokens in
 * @return true The string was succesfully split
 * @return false The string could not be split
 *
 * @note The vector must be initialized before calling this function
 */
bool	lexer(char *input, t_vector *vec)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (checkchar(input[i], "\"\'()") == 1)
		{
			if (!check_delimiters(&input[i]))
				return (err(SYNTAX, "bad quote(s) or parantheses", NULL, NULL), false);
			if (!make_string(input, &i, vec))
				return (err(MALLOC, "malloc", NULL, NULL), false);
		}
		else if (input[i] == ' ')
		{
			if (!create_string(input, &i, vec))
				return (err(MALLOC, "malloc", NULL, NULL), false);
		}
		else
			i++;
	}
	if (i > 0 && checkchar(input[i - 1], "\"\') ") == 0)
		if (!create_string(input, &i, vec))
			return (err(MALLOC, "malloc", NULL, NULL), false);
	return (true);
}
