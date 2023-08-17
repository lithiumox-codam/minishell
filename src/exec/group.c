/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/17 16:13:03 by mdekker/jde   ########   odam.nl         */
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

/**
 * @param	token_vec the token vector
 * @param	group the group to add the new tokens to
 * @param	i to step over the heredoc and the quotes / filenames
 * @param
*/
bool	hdoc_found(t_vector *token_vec, t_group group, int *i)
{
	t_token	*token;
	t_exec	*exec;
	char	*filename;
	t_global	g;

	filename = ft_heredoc(t_types, stopword);


}

/**

ls | cat <<stop | echo <<end | wc

group1: ls
group2: str:cat heredoc:heredocfilename
group4: str:echo heredoc:end
			dus basically verwijder heredoc + following string, vervang ze door een token type:heredoc, value = filename
group3: wc

 * 5. read through the token_vec and check if there is a pipe,
	if there is store the tokens before the pipe in t_pipe
 * 6. if there is no pipes store all of the remaining tokens in t_pipe
 * 7. if there is a pipe check if its a left_pipe,
	middle_pipe or right_pipe and store it in t_pipe correctly
 * 8. once all is complete call the exector
 *
 *
 */
t_exec	*group_tokens(t_vector *token_vec)
{
	size_t		i;
	t_exec		*exec;
	t_vector	group_vec;
	t_group		*group;
	t_token		*token;

	exec = create_exec();
	if (!exec)
		return (NULL);
	i = 0;
	while (i < token_vec->lenght)
	{
		group = create_group();
		if (!group)
			return (ft_vec_free(&group_vec), NULL);
		token = (t_token *)ft_vec_get(token_vec, i);
		while (token->type != PIPE)
		{
			if (token->type == HEREDOC)
				hdoc_found(token_vec, group, &i);
			else
				ft_vec_push(&group->input, (void *)dup_token(&token_vec, token));
			if (i >= token_vec->lenght )
				break ;
			i++;
			token = (t_token *)ft_vec_get(token_vec, i);
		}
		ft_vec_push(&group_vec, group); // push the created group
		if (i >= token_vec->lenght )
				break ;
		i++;
	}
	return (exec);
}
