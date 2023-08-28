/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:06:18 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/28 11:33:48 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	find_operator(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] && !checkchar(token->value[i], "<>|&"))
		i++;
	if (token->value[i] == '\0')
		return (false);
	return (true);
}

/*
static bool	operator_err(char *str)
{
			// & -> fail
		//  aan het einde | of || of && -> vec->index == i, "unfinished sign"
		// aan het begin | of || of && -> vec->index == i,
			"syntax error near unexpected token"
		// < >  vec->index == i, "syntax error near unexpected token `newline'"
		// << >> vec->index == i, syntax error near unexpected token `newline'
	if (str[0] == '&' && str[1] != '&')
			err("nice try, out of scope", "`&'", 2);
	else if (checkchar(str[0], "<>"))
		err("syntax error near unexpected token `newline'", str, 2);
	else if (str[0] == '|' && str[1] != '||')
		err("syntax error near unexpected token", "`|'", 2);
	else if (str[0] == '|' && str[1] == '||')
		err("syntax error near unexpected token", "`|'", 2);
	else if (Str[0] == )
	return (false);
}
*/

static size_t	split_size(char *str)
{
	size_t	split;
	size_t	i;

	split = 0;
	i = 0;
	while (str[i])
	{
		if (checkchar(str[i], "<>|&"))
		{
			split++;
			if (i > 0 && str[i - 1] && !checkchar(str[i - 1], "<>|&"))
				split++;
			if (str[i] == str[i + 1] && str[i] != '&')
				i++;
		}
		i++;
	}
	return (split);
}

static bool	split_left(char *str, char **array, size_t i, size_t *split)
{
	size_t	left;

	left = i;
	if (left > 0 && !checkchar(str[left - 1], "<>|&"))
	{
		left--;
		while (left > 0 && !checkchar(str[left], "<>|&"))
			left--;
		if (checkchar(str[left], "<>|&"))
			left++;
		array[(*split)] = ft_substr(str, left, i - left);
		if (!array[(*split)])
			return (false);
		(*split)++;
	}
	return (true);
}

static bool	split_string(char *str, char **array, size_t *i, size_t *split)
{
	size_t	len;

	if (!split_left(str, array, (*i), split))
		return (false);
	len = 1;
	if (str[(*i)] == str[(*i) + 1] && str[(*i)] != '&')
		len++;
	array[(*split)] = ft_substr(str, (*i), len);
	if (!array[(*split)])
		return (false);
	(*split)++;
	(*i) += len;
	return (true);
}

/**
 *
 *
*/
static char	**split(t_token *token)
{
	size_t	i;
	size_t	split;
	char	**array;

	split = split_size(token->value) + 1;
	array = malloc(sizeof(char *) * (split + 1));
	if (!array)
		return (NULL);
	array[split] = NULL;
	split = 0;
	i = 0;
	while (token->value[i])
	{
		if (checkchar(token->value[i], "<>|&"))
		{
			if (!split_string(token->value, array, &i, &split))
				return (ft_free(array), NULL);
		}
		else
			i++;
	}
	if (!split_left(token->value, array, i, &split))
		return (ft_free(array), NULL);
	return (array);
}

size_t	array_length(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

bool	operator_split(t_vector *vec)
{
	size_t	i;
	size_t	j;
	t_token	*token;
	char	**array;

	i = 0;
	while (i < vec->length)
	{
		token = (t_token *)vec_get(vec, i);
		if (token->type == STRING && find_operator(token))
		{
			array = split(token);
			if (!array || !vec->remove(vec, i))
				return (err("malloc", NULL, 1), false);
			j = 0;
			while (array[j])
			{
				token = create_token(array[j], UNKNOWN);
				if (!token || !vec->insert(vec, i + j, token))
					return (err("malloc", NULL, 1), false);
				j++;
			}
		}
		else
			i++;
	}
	parser(vec);
	if (!array)
		free(array);
	return (true);
}
