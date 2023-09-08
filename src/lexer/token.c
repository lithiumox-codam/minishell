/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:06:18 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/08 16:38:34 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	find_operator(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] && !checkchar(token->value[i], "<>|&"))
		i++;
	if (token->value[i] == '\0')
		return (false);
	return (true);
}

static void	insert_array(t_shell *data, char **array, int i)
{
	int		j;
	t_token	*token;

	j = 0;
	while (array[j])
	{
		token = create_token(array[j], UNKNOWN);
		if (!token || !vec_insert(&data->token_vec, i + j, token))
		{
			ft_free(array);
			err(MALLOC, "malloc", data, true);
		}
		j++;
	}
}

bool	operator_split(t_shell *data)
{
	size_t	i;
	size_t	j;
	t_token	*token;
	char	**array;

	i = 0;
	while (i < (&data->token_vec)->length)
	{
		token = (t_token *)vec_get(&data->token_vec, i);
		if (token->type == STRING && find_operator(token))
		{
			array = split(token);
			if (!array || !vec_remove(&data->token_vec, i))
			{
				ft_free(array);
				return (set_err(MALLOC, "op_split", data));
			}
			insert_array(data, array, i);
		}
		else
			i++;
	}
	if (array)
		free(array);
	return (true);
}
