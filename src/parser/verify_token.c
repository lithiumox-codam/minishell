/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 16:57:32 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/02 20:08:01 by mdekker/jde   ########   odam.nl         */
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

}
