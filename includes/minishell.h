/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/19 15:32:31 by juliusdebaa   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <libft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG 0
#endif

/*
	Lists
*/
t_token *list_append(t_token *head, char *str, t_types type);
t_token *list_insert(t_token *head, char *str, t_types type, size_t index);

/* input_check */
bool check_quotes_parantheses(char *input);
bool	lexer(char *input, t_vector *vec);

/*
	Error handling
*/
void err(char *err, char *cmd, int exit_code);

#endif
