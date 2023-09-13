/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 13:06:18 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/13 18:39:17 by mdekker/jde   ########   odam.nl         */
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
			set_err(MALLOC, "malloc", data);
			break ;
		}
		j++;
	}
}

void	operator_split(t_shell *data)
{
	size_t	i;
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
				set_err(MALLOC, "malloc", data);
				break ;
			}
			insert_array(data, array, i);
			free(array);
		}
		else
			i++;
	}
	parser(data);
}
