/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enum.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:41:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/13 17:42:54 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/**
 * @brief The enum for the different types of tokens
 *
 * @param DOUBLE_QUOTE (")
 * @param SINGLE_QUOTE (')
 * @param SPACE ( )
 * @param PIPE (|)
 * @param SEMICOLON (;)
 * @param REDIRECT (< >)
 * @param END (\0)
 * @param ENV ($)
 * @param ENV_VAR The name of the environment variable
 * @param CHAR Any other character
 */
typedef enum e_types
{
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	SPACE,
	PIPE,
	SEMICOLON,
	REDIRECT,
	END,
	ENV,
	ENV_VAR,
	CHAR,

}	t_types;

#endif
