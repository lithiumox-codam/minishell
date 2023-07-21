/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 13:51:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 18:25:14 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Prints data in a vector in a pretty way
 *
 * @param vec The vector to print
 * @param printer The function to print the data
 */
void	print_vector(t_vector *vec, void (*printer)(void *, size_t))
{
	size_t	i;

	i = 0;
	while (i < vec->lenght)
	{
		printer(vec->get(vec, i), i);
		i++;
	}
}

static char	*extra_types(t_types type)
{
	if (type == AND)
		return ("AND");
	if (type == ENV)
		return ("ENV");
	if (type == DQ_ENV)
		return ("DQ_ENV");
	if (type == STRING)
		return ("STRING");
	if (type == O_REDIRECT)
		return ("O_REDIRECT");
	if (type == I_REDIRECT)
		return ("I_REDIRECT");
	if (type == O_HEREDOC)
		return ("O_HEREDOC");
	if (type == I_HEREDOC)
		return ("I_HEREDOC");
	return ("");
}

/**
 * @brief Prints type names when provided with a token type
 *
 * @param type The t_types enum
 * @return char* The name of the type
 */
char	*print_type(t_types type)
{
	if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	if (type == PIPE)
		return ("PIPE");
	if (type == PARENTHESES)
		return ("PARENTHESES");
	if (type == SEMICOLON)
		return ("SEMICOLON");
	if (type == OR)
		return ("OR");
	if (type == ENV_QUESTION)
		return ("ENV_QUESTION");
	if (extra_types(type)[0] != '\0')
		return (extra_types(type));
	return ("UNKNOWN");
}
