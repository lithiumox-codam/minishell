/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/02 21:31:51 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*

group the tokens into their executable groups

< infile cat | cat -e | wc > outfile

Groups:
"< infile" == start_I_redirect
"wc > outfile" == end_O_redirect

cat == left_process (pipe on the right side, no pipe on the left side)
cat -e == middle_process (pipe on the left side and pipe on the right side)
wc == right_process (pipe on the right side, no pipe on the left side)


< infile cat | cat -e > outfile | echo "hello" | wc

redirects are only handled by main process if they are on the outside, if redirects are not fully on the outside they are handled by the child_processes

groups:
< infile == start_I_redirect

cat == left_process
cat -e > outfile == middle_process
echo "hello" = middle_process
wc = right_process


cmd []


*/
#include <minishell.h>

typedef struct s_local
{
	size_t	left;
	size_t	right;
}			t_local;



static t_local	group_range(t_vector *token_vec, int i)
{
	t_token	*token;
	t_local	range;

	range.left = i;
	token = (t_token *)ft_vec_get(token_vec, i);
	if (token->type == I_REDIRECT)// && i == 0;
		range.right = 2;
	return (range);
}

bool create_group(t_vector *token_vec, t_vector *exec_vec, int *i, t_local range)
{
	t_token	*token;
	t_exec	*exec;



	
}

/**
 * 
*/
bool	group_tokens(t_vector *token_vec, t_vector *exec_vec)
{
	size_t	i;
	t_token	*token;
	t_exec	*exec;
	t_local range;
	char	**cmd;

	i = 0;
	while (i < token_vec->lenght)
	{
		token = (t_token *)ft_vec_get(token_vec, i);
		if (token->type != STRING)
		{
			printf("found non string--%zu\n", i);
			range = group_range(token_vec, i);
			//create_group(t_vector *token_vec, t_vector *exec_vec, int *i)
			cmd = malloc(sizeof(char *) * (range.right + 1));
			if (!cmd)
				return (false);
			while (i < i + range.left + range.right)
			{
				token = (t_token *)ft_vec_get(token_vec, i);
				cmd[i - range.left] = ft_strdup(token->value);
				if (!exec->cmd[i - range.left])
					return (false);
				exec = create_exec(cmd);
				exec_vec->push(exec_vec, (t_exec *) exec);
				i++;
			}
		}
		else
			i++;
	}

	


	if (exec)
		return (true);

	//pos = &cat -> &vec->data
	return (true);
}

