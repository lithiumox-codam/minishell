/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/12 21:19:32 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

group the tokens into their executable groups

< infile cat | cat -e | wc > outfile

Groups:
"< infile" == start_I_redirect --> function
"wc > outfile" == end_O_redirect  --> function

cat == left_process (pipe on the right side, no pipe on the left side)
cat -e == middle_process (pipe on the left side and pipe on the right side)
wc == right_process (pipe on the right side, no pipe on the left side)


< infile cat | cat -e > outfile | echo "hello" | wc

redirects are only handled by main process if they are on the outside,
	if redirects are not fully on the outside they are handled by the child_processes

groups:
< infile == start_I_redirect --> function

cat == left_process -->function
cat -e > outfile == middle_process --> function
echo "hello" = middle_process --> function
wc = right_process --> function

redirects not on the outside should be handled by childprocesses

HEREDOCs should always be handled in the main process ( before forking )
all redirect should be handled before the child process is forked if on the outside
	otherwise it should be handled by the child process

quote expansion		handled by mees

pipes are handled by the child	process(left, right and middle process)

parantheses should be handled beforehand?

AND OR are their own childprocesses? idk still need to look into that

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



------------------------
edge case:
<newfile | cat -e

in this case on the leftside of the pipe there wont be anything
so the left process will be NULL --> meaning no fork should be started for left_pipe
the right process will be cat
	-e --> meaning a fork should be started for right_pipe


to do this keep track of which tokens  have already been read so that when a pipe is found
the left process can be checked if it is NULL or not

*/

* /
#include <minishell.h>

	typedef struct s_local
{
	size_t						left;
	size_t						right;
}								t_local;

// static t_local	group_range(t_vector *token_vec, int i)
// {
// 	t_token	*token;
// 	t_local	range;

// 	range.left = i;
// 	token = (t_token *)ft_vec_get(token_vec, i);
// 	while (token->type != PIPE && token->type != I_REDIRECT
// 		&& token->type != O_REDIRECT && token->type != A_REDIRECT
// 		&& i < token_vec->lenght)
// 	{
// 		i++;
// 		token = (t_token *)ft_vec_get(token_vec, i);
// 	}
// 	return (range);
// }

bool	create_group(t_vector *token_vec, t_vector *exec_vec, int *i,
		t_local range)
{
	t_token	*token;
	t_exec	*exec;
}

/**
 *step by step:
 * 1. check if there is a redirect at the start
 *
 *
 * 	if there is a heredoc or redirect at the start

		* 	create a token for this with the value relating to the type and the value being the stopword/fi;e
 * 	the relating tokens are then removed from the main vector
 *
 * if there is a redirect at the end (heredoc doesnt matter
	- should be handled by verify)
 * 	store the redirect as token,
		the value is the filename and then token is the type of redirect
 * 	then remove the corresponding tokens from the main vector

		store this heredoc stopword as t_token with value set to the stopword
 * 5. read through the token_vec and check if there is a pipe,
	if there is store the tokens before the pipe in t_pipe
 * 6. if there is no pipes store all of the remaining tokens in t_pipe
 * 7. if there is a pipe check if its a left_pipe,
	middle_pipe or right_pipe and store it in t_pipe correctly
 * 8. once all is complete call the exector
 *
 *
 */
bool	group_tokens(t_vector *token_vec, t_vector *exec_vec)
{
	size_t	i;
	t_token	*token;
	t_exec	*exec;
	t_local	range;
	char	**cmd;

	i = 0;
	while (i < token_vec->lenght)
	{
		token = (t_token *)ft_vec_get(token_vec, i);
		if (i == 0 && (token->type == I_REDIRECT))
			redirect_token(token_vec, &i);
		if (i == token->vec->length - 1 || i == token->vec->length - 2)
			&& token->type == O_REDIRECT || token->type == A_REDIRECT))
			redirect_token(token_vec, &i);
	}
	return (true);
}

/*
 < infile cat -e

 <infile == redirect
 cat
	- e is a main process executor? or can i just always create a new process for each command?

*/