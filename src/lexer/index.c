/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:32:55 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/07 14:55:59 by mdekker/jde   ########   odam.nl         */
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

bool	lexer_check_char(char *input, int *i, t_shell *data)
{
	char	temp[2];

	temp[0] = '\0';
	temp[1] = '\0';
	if (checkchar(input[*i], "\"\'()") == 1)
	{
		if (!check_delimiters(&input[*i]))
		{
			temp[0] = input[*i];
			return (set_err(SYNTAX_MINI, temp, data));
		}
		if (!make_string(input, i, &data->token_vec))
			return (set_err(MALLOC, "lexer", data));
	}
	else if (input[*i] == ' ')
	{
		if (!create_string(input, i, &data->token_vec))
			return (set_err(MALLOC, "lexer", data));
	}
	else
		(*i)++;
	return (true);
}

/**
 * @brief Splits a string into token_vec
 *
 * @param input	The string to split
 * @param data	t_shell data, of which token_vec will be used
 */
bool	lexer(char *input, t_shell *data)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (!lexer_check_char(input, &i, data))
			return (false);
	}
	if (i > 0 && checkchar(input[i - 1], "\"\') ") == 0)
		if (!create_string(input, &i, &data->token_vec))
			return (set_err(MALLOC, "lexer", data));
	return (true);
}
