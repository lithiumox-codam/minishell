/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 13:41:35 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 16:35:25 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool create_string(char *str, size_t *i, t_vector *vec)
{
	size_t left;
	size_t right;
	char *value;

	right = (*i);
	while (right > 0 && str[right] == ' ')
		right--;
	if (right > 0 && (str[right] == '\'' || str[right] == '\"' || str[right] == '('))
		right--;
	left = right;
	if (left > 0)
		left--;
	if (left != 0)
	{
		while (left != 0 &&
			   (str[left] != ' ' && str[left] != '\'' && str[left] != '\"' && str[left] != ')'))
			left--;
		if (str[left] == ' ' || str[left] == '\'' || str[left] == '\"' || str[left] == ')')
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
bool create_quote_string(char *str, size_t *i, t_vector *vec)
{
	size_t occur_right;
	char c;
	char *value;

	if ((*i) > 0 && (str[(*i) - 1] != ' ' && str[(*i) - 1] != '\''  && str[(*i) - 1] != '\"' && str[(*i) - 1] != ')'))
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


bool create_paran_string(char *str, size_t *i, t_vector *vec)
{
	size_t occur_right;
	int	parantheses;
	char *value;

	if ((*i) > 0 && (str[(*i) - 1] != ' ' && str[(*i) - 1] != '\''  && str[(*i) - 1] != '\"' && str[(*i) - 1] != ')'))
		create_string(str, i, vec);
	occur_right = (*i) + 1;
	parantheses = 1;
	while (str[occur_right] && parantheses > 0)
	{
		if (str[occur_right] == '(')
			parantheses++;
		else if (str[occur_right] == ')')
			parantheses--;
		occur_right++;
	}
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
