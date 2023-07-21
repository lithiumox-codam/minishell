/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/21 04:20:30 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

bool	init(char **envp);

/* input_check */
bool	check_quotes_parantheses(char *input);
bool	lexer(char *input, t_vector *vec);
bool	create_string(char *str, size_t *i, t_vector *vec);
bool	create_quote_string(char *str, size_t *i, t_vector *vec);
bool	create_paran_string(char *str, size_t *i, t_vector *vec);

/* structs */
t_token	*create_token(char *value, int type);
void	print_token(void *data, size_t i);
void	clear_token(void *data);
t_env	*create_env(char *key, char *value);
void	print_env(void *data, size_t i);
void	clear_env(void *data);
/* utils */
void	err(char *err, char *cmd, int exit_code);

/* parser */
void	parser(t_vector *vec);
bool	is_encased_dq(char *str);
bool	is_encased_sq(char *str);
bool	is_encased_parentheses(char *str);
bool	is_pipe(char *str);
bool	is_r_redirect(char *str);
bool	is_l_redirect(char *str);
bool	is_r_hd(char *str);
bool	is_l_hd(char *str);
bool	contains_env_var(char *str);
bool	is_or(char *str);
bool	is_and(char *str);
/* debug */
void	print_vector(t_vector *vec, void (*printer)(void *, size_t));

/* global */
void	free_global(bool exit);
#endif
