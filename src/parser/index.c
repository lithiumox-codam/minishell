/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   index.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/20 11:12:20 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/20 16:33:32 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_func_map	*return_map(void)
{
	t_func_map	*func_map;

	func_map = (t_func_map *)malloc(sizeof(t_func_map) * 12);
	if (func_map == NULL)
	{
		return (NULL);
	}
	func_map[0] = (t_func_map){is_encased_dq, DOUBLE_QUOTE};
	func_map[1] = (t_func_map){is_encased_sq, SINGLE_QUOTE};
	func_map[2] = (t_func_map){contains_env_var, ENV};
	func_map[3] = (t_func_map){is_and, AND};
	func_map[4] = (t_func_map){is_or, OR};
	func_map[5] = (t_func_map){is_pipe, PIPE};
	func_map[6] = (t_func_map){is_r_redirect, O_REDIRECT};
	func_map[7] = (t_func_map){is_l_redirect, I_REDIRECT};
	func_map[8] = (t_func_map){is_r_hd, O_HEREDOC};
	func_map[9] = (t_func_map){is_l_hd, I_HEREDOC};
	func_map[10] = (t_func_map){NULL, STRING};
	func_map[11] = (t_func_map){NULL, 0};
	return (func_map);
}
void	parser(t_vector *vec)
{
	t_token		*token;
	t_func_map	*func_map;
	size_t		j;
	size_t		i;

	func_map = return_map();
	i = 0;
	while (i < vec->lenght)
	{
		token = (t_token *)ft_vec_get(vec, i);
		if (token->type == 0)
		{
			j = 0;
			while (func_map[j].func != NULL)
				if (!func_map[j].func(token->value))
					j++;
				else
					break ;
			token->type = func_map[j].type;
		}
		i++;
	}
	free(func_map);
}
