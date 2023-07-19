/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 13:32:55 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/19 15:31:21 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	check_next_quote(char *str)
{
	char	quote;

	quote = *str;
	str++;
	while (*str != '\0' && *str != quote)
		str++;
	if (*str == '\0')
		return (false);
	return (true);
};

static bool	create_quote_string(char *str, size_t *i, t_vector *vec)
{
	size_t	occur_left;
	size_t	occur_right;
	char	*sub;
	char	c;
	
	c = str[*i];
	occur_left = *i;
	while ((str[occur_left] != ' ' || str[occur_left] != '\''
			|| str[occur_left != '\"']) && occur_left > 0)
		occur_left--;
	sub = ft_substr(str, occur_left, (*i) - occur_left + 1);
	if (!sub)
		return (false);
	if (!ft_vec_push(vec, sub))
		return (false);
	occur_right = i;
	while (str[occur_right] != c && str[occur_right])
		occur_right++;
	sub = ft_substr(str, (*i) + 1, occur_right - *i);
	if (!sub)
		return (false);
	if (!ft_vec_push(vec, sub))
		return (false);
	*i = occur_right;
	return (true);
}

static bool	create_string(char *str, size_t *i, int space, t_vector *vec)
{
	size_t	left;
	char	*sub;

	left = *i;
	while (left >= 0 && (str[left] != ' ' || str[left] != '\''
			|| str[left] != '\"'))
		left--;
	if (left != 0 && str[left] != ' ')
		left++;
	sub = ft_substr(str, left, (*i) - space);
	if (!sub)
		return (false);
	if (!ft_vec_push(vec, sub))
		return (false);
	while (str[*i] == ' ' && str[*i])
		*i++;
	return (true);
}

bool	lexer(char *input, t_vector *vec)
{
	size_t	i;

	if (!input)
		return (false);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			if (!check_next_quote(&input[i]))
				return (err("malloc", NULL, 1), false);
			if (!create_quote_string(input, &i, vec))
				return (err("malloc", NULL, 1), false);
		}
		else if (input[i] == ' ')
			if (!create_string(input, &i, 1, vec))
				return (err("malloc", NULL, 1), false);
	}
	if (!create_string(input, &i, 0, vec))
				return (err("malloc", NULL, 1), false);
	return (true);
}
