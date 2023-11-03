/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 13:51:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/30 19:01:03 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <execinfo.h>
#include <minishell.h>

void	print_stack_trace(void)
{
	void	*array[10];
	size_t	size;
	char	**strings;
	size_t	i;

	size = backtrace(array, 10);
	strings = backtrace_symbols(array, size);
	printf("Obtained %zd stack frames.\n", size);
	for (i = 0; i < size; i++)
		printf("%s\n", strings[i]);
	free(strings);
}

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
	if (!DEBUG)
		return ;
	while (i < vec->length)
	{
		printer(vec_get(vec, i), i);
		i++;
	}
}

static char	*extra_types(t_types type)
{
	if (type == STRING)
		return ("STRING");
	if (type == O_REDIRECT)
		return ("O_REDIRECT");
	if (type == I_REDIRECT)
		return ("I_REDIRECT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == HDOC_LITERAL)
		return ("HDOC_LITERAL");
	if (type == A_REDIRECT)
		return ("A_REDIRECT");
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
	if (type == PIPE)
		return ("PIPE");
	if (extra_types(type)[0] != '\0')
		return (extra_types(type));
	return ("UNKNOWN");
}

static char	*extra_types_short(t_types type)
{
	if (type == STRING)
		return ("STR");
	if (type == O_REDIRECT)
		return (">");
	if (type == I_REDIRECT)
		return ("<");
	if (type == A_REDIRECT)
		return (">>");
	if (type == HEREDOC)
		return ("<<");
	if (type == HDOC_LITERAL)
		return ("<<_LITERAL");
	return ("");
}

char	*type_symbol(t_types type)
{
	if (type == PIPE)
		return ("|");
	if (extra_types(type)[0] != '\0')
		return (extra_types_short(type));
	return ("UNK");
}
