/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 19:55:34 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/14 12:04:17 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @note currently not including bonus,
	counting & and | only as invidual operators
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
			if (str[i + 1] && str[i] == str[i + 1])
				i++;
			i++;
		}
		if (!checkchar(str[i], "<>|&"))
		{
			split++;
			while (str[i] && !checkchar(str[i], "<>|&"))
				i++;
		}
	}
	return (split);
}

static bool	split_operator(char *str, char **array, size_t *split, size_t *i)
{
	size_t	len;

	len = 1;
	if (str[(*i) + 1] && str[(*i)] == str[(*i) + 1])
		len++;
	array[(*split)] = malloc(sizeof(char *) * (len + 1));
	if (!array[(*split)])
		return (false);
	array[(*split)][len] = '\0';
	array[(*split)][0] = str[(*i)];
	if (str[(*i) + 1] && str[(*i)] == str[(*i) + 1])
		array[(*split)][1] = str[(*i) + 1];
	(*i) += len;
	(*split)++;
	return (true);
}

static bool	split_non_operator(char *str, char **array, size_t *split,
		size_t *i)
{
	size_t	len;

	len = 0;
	while (str[(*i + len)] && !checkchar(str[(*i) + len], "<>|&"))
		len++;
	array[(*split)] = malloc(sizeof(char *) * (len + 1));
	if (!array[(*split)])
		return (false);
	array[(*split)][len] = '\0';
	len = 0;
	while (str[(*i) + len] && !checkchar(str[(*i) + len], "<>|&"))
	{
		array[(*split)][len] = str[(*i) + len];
		len++;
	}
	(*i) += len;
	(*split)++;
	return (true);
}

char	**split(t_token *token)
{
	size_t	i;
	size_t	split;
	char	**array;

	split = split_size(token->value);
	array = ft_calloc((split + 1), sizeof(char *));
	if (!array)
		return (NULL);
	split = 0;
	i = 0;
	while (token->value[i])
	{
		if (checkchar(token->value[i], "<>|&"))
		{
			if (!split_operator(token->value, array, &split, &i))
				return (ft_free(array), NULL);
		}
		else
		{
			if (!split_non_operator(token->value, array, &split, &i))
				return (ft_free(array), NULL);
		}
	}
	return (array);
}
