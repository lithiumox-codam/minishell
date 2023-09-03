/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 11:15:16 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/03 18:53:43 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "enum.h"
/**
 * @brief The struct for the token_vec
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
 * @param	group_vec vec of all of groups to be executed
 * @param	fname_vec vec of all of the hererdoc filenames
 * @note	heredoc files are to be deleted after execution is completed
 */
typedef struct s_exec
{
	t_vector	group_vec;
	t_vector	fname_vec;
}				t_exec;

/**
 * @brief a group to be individually executed.
 *
 *	@param input	a vector of t_token_vec belonging to 1 child_process
	@param cmd an array containing the commands and parameters to be executed
	@param hdoc_vec vector with heredoc filedescriptors
	@param pd the pd of this specific process
	@param left_pipe the pipe related to the process happening on the left
	@param right_pipe the pipe related to the process happening on the right of this one
	@warning the heredoc file is to be deleted after usage
 */
typedef struct s_group
{
	t_vector	input;
	char		**cmd;
	pid_t		pd;
	int			left_pipe[2];
	int			right_pipe[2];
}				t_group;

/**
 * @brief The global struct
 *
 * @param token_vec The token_vec vector from the lexer and parser;
 * @param env The environment variables;
 * @param data to be passed to the executor;
 */
typedef struct s_shell
{
	t_vector	token_vec;
	t_vector	env;
	t_exec		*exec;
	int			exit_status;
}				t_shell;


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
