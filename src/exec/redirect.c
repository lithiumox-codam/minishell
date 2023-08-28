/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:32:48 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/28 11:29:57 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
	redirects need to remove the tokens related to the redirect

*/

#include <minishell.h>

void handle_redirects(t_vector *group)
{
	size_t	i;
	t_token	*token;

	i = 0;
	while (i < (&group->input)->length)
	{
		token = vector_get(&group->input, i);
		if (token->type == I_REDIRECT || token->type == O_REDIRECT
			|| token->type == A_REDIRECT)
		{
			redirect_input(group, i);
			i = 0;
		}
		else
		i++;
	}
}

//redirect_input()

//in_rediect

//out_redirect

//append_redirect
