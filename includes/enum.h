/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:41:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/22 23:31:57 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/**
 * @brief The enum for the different types of token_vec
 *
 * @param UNKNOWN An unknown type
 * @param STRING A string
 * @param PIPE (|)
 * @param O_REDIRECT (>)
 * @param I_REDIRECT (<)
 * @param A_REDIRECT (>>)
 * @param HEREDOC (<<)
 * @param HDOC_LITERAL (<<) with no expansion
 */
typedef enum e_types
{
	UNKNOWN,
	STRING,
	PIPE,
	O_REDIRECT,
	I_REDIRECT,
	A_REDIRECT,
	HEREDOC,
	HDOC_LITERAL
}	t_types;

/**
 * @brief The enum for the different types of errors
 *
 * @param PERR A PERR
 * @param NOT_FOUND A not found error
 * @param PERMISSION A permission error
 * @param NO_SUCH A No such file or dir error
 * @param SYNTAX A syntax error
 * @param SYNTAX_MINI A syntax error for the minishell
 * @param SIGNAL_C A signal interrupt
 *
 */
typedef enum e_exit
{
	GOOD,
	PERR,
	MALLOC,
	NOT_FOUND,
	PERMISSION,
	NO_SUCH,
	SYNTAX,
	SYNTAX_MINI,
	SIGNAL_C,
	OUT_OF_SCOPE
}	t_exit;

typedef enum e_error
{
	NO_ERROR = 0,
	CATCH_ALL = 1,
	MISUSE_OF_SHELL = 2,
	PERMISSION_DENIED = 126,
	COMMAND_NOT_FOUND = 127,
	NOT_VALID = 128,
	UNEXPECTED_EOF = 130,
	SYNTAX_ERROR = 2,
}	t_error;

/**
 * @brief defines which process is being executed
 */
typedef enum e_process
{
	SINGLE,
	LEFT,
	MIDDLE,
	RIGHT,
}	t_process;

#endif
