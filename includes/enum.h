/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:41:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/12 20:25:03 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/**
 * @brief The enum for the different types of tokens
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
	OR,
	AND,
	ENV,
	DQ_ENV,
	ENV_QUESTION,
	O_REDIRECT,
	I_REDIRECT,
	A_REDIRECT,
	HEREDOC
}	t_types;

#endif
