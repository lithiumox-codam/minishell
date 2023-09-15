/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/09 21:25:59 by mdekker       #+#    #+#                 */
/*   Updated: 2023/09/13 21:39:16 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

/* init shell */
t_shell	*init_shell(char **env, bool first_init);
void	free_shell(t_shell *data, bool close_shell);

/* lexer */
bool	lexer(char *input, t_shell *data);
bool	make_string(char *str, size_t *i, t_vector *vec);
bool	check_quotes_parantheses(char *input);
bool	create_string(char *str, size_t *i, t_vector *vec);
bool	create_quote_string(char *str, size_t *i, t_vector *vec);
bool	create_paran_string(char *str, size_t *i, t_vector *vec);
void	operator_split(t_shell *data);
char	**split(t_token *token);

/* parser */
void	parser(t_shell *data);
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
void	verify_token_vec(t_shell *data);
bool	check_tokens(t_shell *data);
/* group */
void	group_token_vec(t_shell *data);
void	heredoc(char *filename, char *stop, t_types type, t_shell *data);

/* executor */
int		executor(t_shell *data);
bool	create_processes(t_shell *data);
void	exec_process(t_group *group, t_process type);
void	redirect_input(t_group *group, size_t i);

/* exec_utils */
bool	is_built_in(char *str);
char	**combine_env(t_vector *env_vec);
char	**create_cmd(t_vector *input);
bool	is_redirect(t_token *token);
bool	is_string_type(t_token *token);

/* structs */
t_token	*create_token(char *value, t_types type);
void	clear_token(void *data);
t_token	*dup_token(t_token *input);
t_env	*create_env(char *key, char *value);
void	clear_env(void *data);
t_group	*create_group(void);
void	clear_group(void *data);
void	clear_fname(void *data);
t_exec	*create_exec(void);
void	clear_exec(t_exec *exec);

/* general utils */
void	exit_mini(char *str, int exit_code);
bool	set_err(t_exit type, char *msg, t_shell *data);
void	write_err(t_shell *data);
t_token	*rm_quotes(t_token *token);
bool	type_compare(size_t num_args, t_types type, ...);

/* debug */
void	print_vector(t_vector *vec, void (*printer)(void *, size_t));
void	print_token(void *data, size_t i);
char	*print_type(t_types type);
char	*type_symbol(t_types type);
void	print_env(void *data, size_t i);

#endif
