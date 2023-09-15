/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   op_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 19:55:34 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/13 21:41:49 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	**split(t_token *token)
{
	size_t	i;
	size_t	split;
	char	**array;

	split = split_size(token->value);
	array = malloc(sizeof(char *) * (split + 2));
	if (!array)
		return (NULL);
	array[split + 1] = NULL;
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
