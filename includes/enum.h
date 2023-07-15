/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:41:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/15 15:09:31 by mdekker/jde   ########   odam.nl         */
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
 * @param SEMICOLON (;)
 * @param OR (||)
 * @param ENV ($)
 * @param DQ_ENV An environment variable in double quotes ("$")
 * @param STRING A string
 * @param O_REDIRECT (>)
 * @param I_REDIRECT (<)
 * @param HERE_DOC (<<)
 */
typedef enum e_types
{
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	PIPE,
	SEMICOLON,
	OR,
	ENV,
	DQ_ENV,
	STRING,
	O_REDIRECT,
	I_REDIRECT,
	HERE_DOC
}	t_types;

#endif
