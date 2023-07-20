/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 11:15:16 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/20 20:30:18 by mdekker/jde   ########   odam.nl         */
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
	t_types		type;
	char		*value;
}				t_token;

typedef struct env
{
	char		*key;
	char		*value;
}				t_env;

/**
 * @brief THe strt for signals
 *
 * @param quit The quit signal
 * @param interrupt The interrupt signal
 * @param pipe The pipe signal
 */
typedef struct s_signal
{
	bool		quit;
	bool		inte;
	bool		pipe;
}				t_signal;

/**
 * @brief The global struct
 *
 * @param tokens The tokens vector from the lexer and parser
 * @param env The environment variables
 */
typedef struct s_global
{
	t_vector	tokens;
	t_vector	env;
	t_signal	signal;
	char		*exit_status;

}				t_global;

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
	bool		(*func)(char *);
	t_types		type;
}				t_func_map;

#endif
