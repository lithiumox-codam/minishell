/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 21:12:42 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/14 20:24:18 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	free_found(t_vector *found)
{
	vec_free(found);
	free(found);
}

/**
 * @brief Checks if the tokens contain OR and AND operators because they
 * are bonus and were not implementing that.
 * @param found The vector of found tokens
 *
 * @return true The tokens do not contain OR and AND operators
 * @return false The tokens do contain OR and AND operators
 */
bool	out_of_scope(t_vector *found, t_shell *data)
{
	size_t i;
	t_found *current_found;
	t_token *current_token;
	i = 0;
	while (i < found->length)
	{
		current_found = (t_found *)vec_get(found, i);
		current_token = (t_token *)current_found->item;
		print_t_found(current_found, i);
		if (current_token->type == AND || current_token->type == OR)
			return (set_err(OUT_OF_SCOPE, type_symbol(current_token->type),
					data), false);
		i++;
	}
	return (true);
}