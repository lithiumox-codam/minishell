/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 13:41:35 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 04:40:27 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Struct to store the left and right index of a string
 */
typedef struct s_local
{
	int		left;
	int		right;
}			t_local;

/**
 * @brief Builds a string from a given string
 *
 * @param str The string to build from
 * @param vec The vector to push the string to
 * @param x The left and right index of the string
 * @return true The string was built and pushed to the vector
 * @return false The string was not built and not pushed to the vector
 */
static bool	build_string(char *str, t_vector *vec, t_local x)
{
	char	*value;

	while (x.left != 0 && checkchar(str[x.left], "\'\") ") == 0)
		x.left--;
	if (checkchar(str[x.left], "\'\") ") == 1)
		x.left++;
	value = ft_substr(str, x.left, x.right - x.left + 1);
	if (!value)
		return (false);
	if (!vec->push(vec, (void *)create_token(value, 0)))
		return (false);
	return (true);
}

/**
 * @brief Create a string from different characters
 *
 * @param str The string to create from
 * @param i The index of the string to create from
 * @param vec The vector to push the string to
 * @return true The string was created and pushed to the vector
 * @return false The string was not created and not pushed to the vector
 */
bool	create_string(char *str, size_t *i, t_vector *vec)
{
	t_local	x;

	x.right = (*i);
	while (x.right > 0 && str[x.right] == ' ')
		x.right--;
	if (x.right > 0 && checkchar(str[*i], "\'\"(") == 1)
		x.right--;
	x.left = x.right;
	if (x.left > 0)
		x.left--;
	if (x.left != 0)
		build_string(str, vec, x);
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	return (true);
}

/**
 * @brief Create a quote string object
 *
 * @param str The string to create from
 * @param i The index of the string to create from
 * @param vec The vector to push the string to
 * @return true The string was created and pushed to the vector
 * @return false The string was not created and not pushed to the vector
 */
bool	create_quote_string(char *str, size_t *i, t_vector *vec)
{
	size_t	occur_right;
	char	c;
	char	*value;

	if ((*i) > 0 && checkchar(str[(*i) - 1], " \'\")") == 0)
		create_string(str, i, vec);
	c = str[*i];
	occur_right = (*i) + 1;
	while (str[occur_right] && str[occur_right] != c)
		occur_right++;
	occur_right++;
	value = ft_substr(str, *i, occur_right - (*i));
	if (!value)
		return (false);
	if (!vec->push(vec, (void *)create_token(value, 0)))
		return (false);
	*i = occur_right;
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	return (true);
}

/**
 * @brief Create a paran string object
 *
 * @param str The string to create from
 * @param i The index of the string to create from
 * @param vec The vector to push the string to
 * @return true The string was created and pushed to the vector
 * @return false The string was not created and not pushed to the vector
 */
bool	create_paran_string(char *str, size_t *i, t_vector *vec)
{
	size_t	occur_right;
	int		parantheses;
	char	*value;

	if ((*i) > 0 && checkchar(str[(*i) - 1], " \'\")") == 0)
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
	if (!vec->push(vec, (void *)create_token(value, 0)))
		return (false);
	*i = occur_right;
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	return (true);
}
