/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:32:55 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 18:33:58 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

bool	lexer(char *input, t_vector *vec)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (checkchar(input[i], "\"\'()") == 1)
		{
			if (!check_delimiters(&input[i]))
				return (err("bad quote(s) or parantheses", NULL, 1), false);
			if (!make_string(input, &i, vec))
				return (err("malloc", NULL, 1), false);
		}
		else if (input[i] == ' ')
		{
			if (!create_string(input, &i, vec))
				return (err("malloc", NULL, 1), false);
		}
		else
			i++;
	}
	if (checkchar(input[i], "\"\') ") == 0)
		if (!create_string(input, &i, vec))
			return (err("malloc", NULL, 1), false);
	return (true);
}
