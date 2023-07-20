/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:32:55 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 13:36:55 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static bool create_string(char *str, size_t *i, t_vector *vec)
{
	size_t left;
	size_t right;
	char *value;

	right = (*i);
	while (right > 0 && str[right] == ' ')
		right--;
	if (right > 0 && (str[right] == '\'' || str[right] == '\"'))
		right--;
	left = right;
	if (left > 0)
		left--;
	if (left != 0)
	{
		while (left != 0 &&
			   (str[left] != ' ' && str[left] != '\'' && str[left] != '\"'))
			left--;
		if (str[left] == ' ' || str[left] == '\'' || str[left] == '\"')
			left++;
		value = ft_substr(str, left, right - left + 1);
		if (!value)
			return (false);
		if (!ft_vec_push(vec, (void *)create_token(value, 0)))
			return (false);
	}
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	return (true);
}
/**
 * @todo "        hello'gmarmopg    grnrga'     'hey'"; check spaces runback
 */
static bool create_quote_string(char *str, size_t *i, t_vector *vec)
{
	size_t occur_right;
	char c;
	char *value;

	if ((*i) > 0 && (str[(*i) - 1] != ' ' && str[(*i) - 1] != '\'' && str[(*i) - 1] != '\"'))
		create_string(str, i, vec);
	c = str[*i];
	occur_right = (*i) + 1;
	while (str[occur_right] && str[occur_right] != c)
		occur_right++;
	occur_right++;
	value = ft_substr(str, *i, occur_right - (*i));
	if (!value)
		return (false);
	if (!ft_vec_push(vec, (void *)create_token(value, 0)))
		return (false);
	*i = occur_right;
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	return (true);
}

bool lexer(char *input, t_vector *vec)
{
	size_t i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (!check_next_quote(&input[i]))
				return (err("unfinished quote", NULL, 1), false);
			if (!create_quote_string(input, &i, vec))
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
	if (input[i - 1] != ' ' && input[i - 1] != '\'' && input[i - 1] != '\"')
		if (!create_string(input, &i, vec))
			return (err("malloc", NULL, 1), false);
	return (true);
}
