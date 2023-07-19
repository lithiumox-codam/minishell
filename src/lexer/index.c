/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:32:55 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/19 21:59:55 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token *create_token(char *value, int type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

static bool check_next_quote(char *str)
{
	char quote;

	quote = *str;
	str++;
	while (*str != '\0' && *str != quote)
		str++;
	if (*str == '\0')
		return (false);
	return (true);
};
static bool create_quote_string(char *str, size_t *i, t_vector *vec)
{
	size_t occur_left;
	size_t occur_right;
	char c;
	char *value;
	c = str[*i];
	if (i != 0)
	{
		occur_left = (*i) - 1;
		while ((str[occur_left] != ' ' || str[occur_left] != '\'' ||
				str[occur_left != '\"']) &&
			   occur_left > 0)
			occur_left--;
		value = ft_substr(str, occur_left, (*i) - occur_left + 1);
		if (!value)
			return (false);
		if (!ft_vec_push(vec, (void *)create_token(value, -1)))
			return (false);
	}
	occur_right = (*i)++;
	while (str[occur_right] != c && str[occur_right])
		occur_right++;
	value = ft_substr(str, *i, occur_right - *i);
	if (!value)
		return (false);
	if (!ft_vec_push(vec, (void *)create_token(value, -1)))
		return (false);
	*i = occur_right;
	return (true);
}

static bool create_string(char *str, size_t *i, t_vector *vec)
{
	size_t left;
	char *value;

	if (*i != 0)
	{
		left = (*i) - 1;
		while (left != 0 &&
			   (str[left] != ' ' && str[left] != '\'' && str[left] != '\"'))
			left--;
		if (str[left] == ' ' || str[left] == '\'' || str[left] == '\"')
			left++;
		value = ft_substr(str, left, ((*i) - left));
		if (!value)
			return (false);
		if (!ft_vec_push(vec, (void *)create_token(value, -1)))
			return (false);
	}
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	return (true);
}

bool lexer(char *input, t_vector *vec)
{
	size_t i;

	if (!input)
		return (false);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (!check_next_quote(&input[i]))
				return (err("malloc", NULL, 1), false);
			if (i > 0 && !create_quote_string(input, &i, vec))
				return (err("malloc", NULL, 1), false);
		}
		else if (input[i] == ' ')
		{
			if (!create_string(input, &i, vec))
				return (err("malloc", NULL, 1), false);
		}
		else
		{
			i++;
		}
	}
	if (!create_string(input, &i, vec))
		return (err("malloc", NULL, 1), false);
	return (true);
}
