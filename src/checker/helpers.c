/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 21:12:42 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/13 12:33:31 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_found	*get_next_found(t_vector *found, size_t i)
{
	t_found	*next_found;

	next_found = (t_found *)vec_get(found, i + 1);
	if (next_found == NULL)
		return (NULL);
	return (next_found);
}

t_found	*get_current_found(t_vector *found, size_t i)
{
	t_found	*current_found;

	current_found = (t_found *)vec_get(found, i);
	return (current_found);
}

/**
 * @brief Cheks if the type is in the list of types
 *
 * @param num_args The number of types to check against
 * @param type The type to check
 * @param ... The list of types to check against
 * @return true The type is in the list
 * @return false The type is not in the list
 *
 * @warning The number of types to check against must be passed as the first
 * argument to the function. This is because of the way variadic arguments
 * work in C. (unfortunately)
 */
bool	type_compare(size_t num_args, t_types type, ...)
{
	bool	found;
	va_list	args;
	t_types	arg_type;

	if (num_args == 0)
		return (false);
	found = false;
	va_start(args, type);
	while (num_args > 0)
	{
		arg_type = va_arg(args, t_types);
		if (arg_type == type)
		{
			found = true;
			break ;
		}
		num_args--;
	}
	va_end(args);
	return (found);
}
