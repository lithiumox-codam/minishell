/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:41:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/26 14:37:41 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/**
 * @brief The enum for the different types of token_vec
 *
 * @param DOUBLE_QUOTE (")
 * @param SINGLE_QUOTE (')
 * @param PIPE (|)
 * @param PARENTHESES (())
 * @param OR (||)
 * @param AND (&&)
 * @param ENV ($)
 * @param DQ_ENV An environment variable in double quotes ("$")
 * @param ENV_QUESTION An environment variable with a question mark ("$?")
 * @param STRING A string
 * @param O_REDIRECT (>)
 * @param I_REDIRECT (<)
 * @param A_REDIRECT (>>)
 * @param HEREDOC (<<)
 */
typedef enum e_types
{
	UNKNOWN,
	STRING,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	PARENTHESES,
	PIPE,
	ENV,
	DQ_ENV,
	ENV_QUESTION,
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
