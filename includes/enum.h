/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:41:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/20 17:15:53 by mdekker/jde   ########   odam.nl         */
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
 * @param SEMICOLON (;)
 * @param OR (||)
 * @param AND (&&)
 * @param ENV ($)
 * @param DQ_ENV An environment variable in double quotes ("$")
 * @param STRING A string
 * @param O_REDIRECT (>)
 * @param I_REDIRECT (<)
 * @param O_HEREDOC (>>)
 * @param I_HEREDOC (<<)
 */
typedef enum e_types
{
	UNKNOWN,
	STRING,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	PARENTHESES,
	PIPE,
	SEMICOLON,
	OR,
	AND,
	ENV,
	DQ_ENV,
	O_REDIRECT,
	I_REDIRECT,
	O_HEREDOC,
	I_HEREDOC
}	t_types;

#endif
