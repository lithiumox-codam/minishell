/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/12 18:45:24 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	add_redirect(t_token *token, t_group *group, size_t i, t_shell *data)
{
	t_token	*dup;

	if (token->type == HEREDOC)
		return (hdoc_found(group, i, data));
	dup = dup_token(token);
	if (!dup)
		return (set_err(MALLOC, "add_redirect", data));
	if (token->type == I_REDIRECT)
	{
		if (!vec_push(&group->in_red, (void *)dup))
			return (set_err(MALLOC, "add_redirect", data));
	}
	if (token->type == O_REDIRECT || token->type == A_REDIRECT)
	{
		if (!vec_push(&group->out_red, (void *)dup))
			return (set_err(MALLOC, "add_redirect", data));
	}
	return (true);
}

bool	alloc_args(t_group *group, size_t i, t_shell *data)
{
	size_t	size;
	t_token	*token;

	size = 0;
	while (i < (&data->token_vec)->length)
	{
		token = (t_token *)vec_get(&data->token_vec, i);
		if (token->type == PIPE)
			break ;
		if (token->type == STRING)
			size++;
		i++;
	}
	if (size == 0)
		group->args = NULL;
	else
	{
		group->args = ft_calloc((size + 1), sizeof(char *));
		if (!group->args)
			return (set_err(MALLOC, "group_tokens", data));
		group->args[size] = NULL;
	}
	return (true);
}

/**

	* @note check the else statement depending on how we will handle quotes (ie. could be else if (token->type == STRING
		|| token->type == QUOTE_STRING)
 *
 */
static bool	group_tokens(t_group *group, size_t *i, t_shell *data)
{
	size_t	i_arg;
	t_token	*token;

	i_arg = 0;
	while ((*i) < (&data->token_vec)->length)
	{
		token = (t_token *)vec_get(&data->token_vec, (*i));
		if (token->type == PIPE)
			break ;
		if (is_redirect(token))
		{
			if (!add_redirect(token, group, (*i), data))
				return (false);
		}
		else
		{
			group->args[i_arg] = ft_strdup(token->value);
			if (!group->args[i_arg])
				return (set_err(MALLOC, "group_tokens", data));
			i_arg++;
		}
		(*i)++;
	}
	return (true);
}

static bool	set_cmd(t_group *group, size_t i, t_shell *data)
{
	t_token	*token;

	while (i < (&data->token_vec)->length)
	{
		if (token->type == PIPE)
			break ;
		token = (t_token *)vec_get(&data->token_vec, i);
		if (token->type == STRING)
		{
			group->cmd = ft_strdup(token->value);
			if (!group->cmd)
				return (set_err(MALLOC, "set_cmd", data));
			return (true);
		}
		i++;
	}
	group->cmd = NULL;
	return (true);
}

/**
 * @brief Group the token_vec into groups
 *
 * @param token_vec The vector containing the token_vec
 * @return t_exec* The struct containing the groups
 */
bool	group_token_vec(t_shell *data)
{
	size_t	i;
	t_group	*group;

	data->exec = create_exec();
	if (!data->exec)
		return (set_err(MALLOC, "group_token_v", data));
	i = 0;
	while (i < (&data->token_vec)->length)
	{
		group = create_group();
		if (!group)
			return (set_err(MALLOC, "group_token_v", data));
		if (!set_cmd(group, i, data))
			return (false);
		if (!alloc_args(group, i, data))
			return (false);
		if (!group_tokens(group, &i, data))
			return (false);
		if (!vec_push(&data->exec->group_vec, group))
			return (set_err(MALLOC, "group_token_v", data));
		i++;
	}
	return (true);
}
