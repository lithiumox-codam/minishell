/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/08 17:56:34 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	add_redirect(t_group *group, int i, t_shell *data)
{
	t_token	*token;
	t_token	*dup;

	token = (t_token *)vec_get(&data->token_vec, i);
	if (token->type == HEREDOC)
	{
		hdoc_found(group, i, data);
		return (true);
	}
	if (token->type == I_REDIRECT)
	{
		dup = dup_token(token);
		if (!dup)
			return (set_err(MALLOC, "add_redirect", data));
		if (!vec_push(&group->in_red, (void *)dup))
			return (set_err(MALLOC, "add_redirect", data));
	}
	if (token->type == O_REDIRECT || token->type == A_REDIRECT)
	{
		dup = dup_token(token);
		if (!dup)
			return (set_err(MALLOC, "add_redirect", data));
		if (!vec_push(&group->out_red, (void *)dup))
			return (set_err(MALLOC, "add_redirect", data));
	}
}

bool	set_args(t_group *group, int i, t_shell *data)
{
	size_t	size;
	t_token	*token;

	token = (t_token *)vec_get(&data->token_vec, i);
	while (i < (&data->token_vec)->length && token->type != PIPE)
	{
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

static bool	group_tokens(t_group *group, int *i, t_shell *data)
{
	size_t	i_arg;
	t_token	*token;

	if (!set_args(group, *i, data))
		return (false);
	token = (t_token *)vec_get(&data->token_vec, (*i));
	i_arg = 0;
	while (i < (&data->token_vec)->length && token->type != PIPE)
	{
		if (is_redirect(token))
		{
			if (!add_redirect(group, i, data))
				return (false);
		}
		if (token->type == STRING)
		{
			group->args[i_arg] = ft_strdup(token->value);
			if (!group->args[i_arg])
				return (set_err(MALLOC, "group_tokens", data));
			i_arg++;
		}
		i++;
	}
	return (group);
}

static bool	set_cmd(t_group *group, int i, t_shell *data)
{
	t_token	*token;

	token = (t_token *)vec_get(&data->token_vec, i);
	while (i < (&data->token_vec)->length && token->type != PIPE)
	{
		if (token->type == STRING)
		{
			group->cmd = ft_strdup(token->value);
			if (!group->cmd)
				return (set_err(MALLOC, "set_cmd", data));
			return (true);
		}
	}
	group->cmd == NULL;
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
	t_exec	*exec;
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
		group_tokens(group, &i, data);
		if (!vec_push(&exec->group_vec, group))
			return (set_err(MALLOC, "group_token_v", data));
		i++;
	}
	return (true);
}
