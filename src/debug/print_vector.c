/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_vector.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 13:51:45 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 03:47:23 by mdekker/jde   ########   odam.nl         */
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
