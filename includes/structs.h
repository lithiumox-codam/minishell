/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 11:15:16 by mdekker       #+#    #+#                 */
/*   Updated: 2023/08/11 12:24:08 by mdekker/jde   ########   odam.nl         */
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
 * @note The value is malloced
 */
typedef struct s_token
{
	t_types		type;
	char		*value;
}				t_token;

/**
 * @brief The struct for the environment variables
 *
 * @param key The key of the variable
 * @param value The value of the variable
 *
 * @note The key and value are both malloced
 */
typedef struct env
{
	char		*key;
	char		*value;
}				t_env;

/**
 * @brief The struct for signals
 *
 * @param quit The quit signal (ctrl + D)
 * @param inte The interrupt signal (ctrl + C)
 * @param pipe The pipe signal (ctrl + \)
 */
typedef struct s_signal
{
	bool		quit;
	bool		inte;
	bool		pipe;
}				t_signal;

/**
 * @brief The struct for the execution
 *
 * @param pipes The vector of pipes
 * @param here_doc The here_doc stop-word token
 * @param input_redirect The input_redirect file to read from
 * @param output_redirect The output_redirect file to write to
 */
typedef struct s_exec
{
	t_vector	pipes;
	t_token		here_doc;
	t_token		input_redirect;
	t_token		output_redirect;
}				t_exec;

/**
 * @param locate 0 == no pipe
 * @param locate 1 == left_process
 * @param locate 2 == middle_process
 * @param locate 3 == right_process
 */
typedef struct s_pipe
{
	char		**cmd;
	pid_t		pd;
	int			locate;
	int			right_pipe[2];
	int			left_pipe[2];
} t_pipe; //

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
	t_pipe		exec;
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
