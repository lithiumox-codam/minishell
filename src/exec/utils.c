/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 19:44:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/01 21:37:27 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_built_in(char *str)
{
	if (ft_strcmp(str, "exit") == 0) //@note or any of the other strings
		return (true);
}

char	**combine_env(t_vector *env_vec)
{

}



bool is_redirect(t_token *token)
{
	if (token->type == O_REDIRECT || token->type == I_REDIRECT
		|| token->type == A_REDIRECT || token->type == HEREDOC)
	{
		return (true);
	}
	return (false);
}
