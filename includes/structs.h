/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 11:15:16 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/20 16:26:31 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "enum.h"
/**
 * @brief The struct for the tokens
 *
 * @param type The type of token
 * @param value The value of the token
 * @param prev The previous token
 * @param next The next token
 */
typedef struct s_token
{
	t_types	type;
	char	*value;
}			t_token;

/**
 * @brief The struct for the parser functions.
 *
 * @param func The function to be called
 * @param type The type of token the function is for
 *
 * @see t_types
 *
 * @note The function should return true if the token
 * is that type, false if not.
 */
typedef struct s_func_map
{
	bool	(*func)(char *);
	t_types	type;
}			t_func_map;

#endif
