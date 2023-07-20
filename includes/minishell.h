/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/20 14:05:44 by mdekker/jde   ########   odam.nl         */
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

/* input_check */
bool check_quotes_parantheses(char *input);
bool lexer(char *input, t_vector *vec);

/* structs */
t_token *create_token(char *value, int type);
void clear_token(void *data);
/* utils */
void err(char *err, char *cmd, int exit_code);

/* parser */
void parser(t_vector *vec);
bool is_encased_dq(char *str);
bool is_encased_sq(char *str);

/* debug */
void print_token_vector(t_vector *tokens);

#endif
