/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   combine_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 18:02:02 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/03 17:12:24 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**combine_cmd(t_group *group)
{
	char	**cmd;
	size_t	count;

	count = cmd_count(&group->input, false);
	if (count == 0)
		return (NULL);
	cmd = malloc(sizeof(char *) * count + 1);
	if (!cmd)
		err(MALLOC, "create_cmd", NULL, NULL);
	cmd[count] = NULL;
	cmd = assign_token_vec(cmd, cmd_count(&group->input, true), &group->input);
	return (cmd);
}

/**
 * @brief assigns the token_vec to the cmd;
*/
char	**assign_token_vec(char **cmd, size_t start, t_vector *input)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (start < input->length && !is_redirect(token))
	{
		token = vec_get(input, start);
		if (i == 0)
			cmd[i] = ft_strdup(rm_quotes(token->value));
		else
			cmd[i] = ft_strdup(token->value);
		if (!cmd[i])
			err(MALLOC, "create_cmd", NULL, NULL);
		start++;
		i++;
	}
}

/**
 * @brief counts the amount of token_vec in the vector skipping redirects
 * @param	start if true it will return the index after the starting redirects
 * @param 	start if false it will return the amount of non-redirect token_vec
*/
static size_t	cmd_count(t_vector *input, bool start)
{
	char	**cmd;
	t_token	*token;
	size_t		i;
	size_t	count;

	i = 0;
	count = 0;
	token = (t_token *)vec_get(input, i);
	while (i < input->length && is_redirect(token))
	{
		i++;
		if (i < input->length)
			token = (t_token *)vec_get(input, i);
	}
	if (start == true)
		return (i);
	while (i < input->length && !is_rediect(token))
	{
		count++;
		i++;
		token = (t_token *)vec_get(input, i);
	}
	return (count);
}
