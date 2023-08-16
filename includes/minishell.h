/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/08/16 16:21:36 by mdekker/jde   ########   odam.nl         */
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
bool	lexer(char *input, t_vector *vec);
bool	check_quotes_parantheses(char *input);
bool	create_string(char *str, size_t *i, t_vector *vec);
bool	create_quote_string(char *str, size_t *i, t_vector *vec);
bool	create_paran_string(char *str, size_t *i, t_vector *vec);
bool	operator_split(t_vector *vec);

/* structs */
t_token	*create_token(char *value, t_types type);
void	clear_token(void *data);
t_env	*create_env(char *key, char *value);
void	clear_env(void *data);
t_exec	*create_exec(void);
void	clear_exec(void *data);

/* utils */
void	err(char *err, char *cmd, int exit_code);

/* parser */
void	parser(t_vector *vec);
void	parse_one(t_token *token);
bool	is_encased_dq(char *str);
bool	is_encased_sq(char *str);
bool	is_encased_parentheses(char *str);
bool	is_pipe(char *str);
bool	is_r_redirect(char *str);
bool	is_l_redirect(char *str);
bool	is_a_redirect(char *str);
bool	is_heredoc(char *str);
bool	contains_env_var(char *str);
bool	is_or(char *str);
bool	is_and(char *str);

/* executor */
bool	group_tokens(t_vector *token, t_vector *exec);

/* debug */
void	print_vector(t_vector *vec, void (*printer)(void *, size_t));
void	print_token(void *data, size_t i);
char	*print_type(t_types type);
void	print_env(void *data, size_t i);

/* global */
void	free_global(bool exit);

#endif
