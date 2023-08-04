/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/03 12:46:53 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
check for double operators
check for starting with anything other token than redirects / heredoc

geen I_INDIRECT aan het einde

Na een operator mag je alleen STRING/DOUBLE_QUOTE/SINGLE_QUOTE

na een pipe mag je wel < > << >>

bash-3.2$ <|hello
bash: syntax error near unexpected token `|'
bash-3.2$ cat infile |< bruh
bash: bruh: No such file or directory

*/
bool	verify_token(t_vector *vec)
{
	int		i;
	t_token	*token;

	if (vec->len == 0)
		return (false);
	token = vec->data[0];
	if (token->type != I_REDIRECT && token->type != I_HEREDOC)
		return (false);
	token = vec->data[vec->len - 1];
	if (token->type != I_REDIRECT && token->type != I_HEREDOC)
		return (false);
	i = 0;
	while (i < vec->len - 1)
	{
		token = vec->data[i];
		if (token->type == I_PIPE && ((t_token *)vec->data[i
				+ 1])->type == I_PIPE)
			return (false);
		i++;
	}
	return (true);
}
