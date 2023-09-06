/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/06 20:36:35 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	push_hdoc(char *filename, t_group *group, t_shell *data)
{
	char	*fname;
	t_token	*red_token;
	t_token	*fname_token;

	fname = ft_strdup(filename);
	if (!fname)
		err(MALLOC, "push_hdoc", data, true);
	fname_token = create_token(filename, STRING);
	if (!fname_token)
		err(MALLOC, "push_hdoc", data, true);
	red_token = create_token("<", I_REDIRECT);
	if (!red_token)
		err(MALLOC, "push_hdoc", data, true);
	if (!vec_push(&group->input, (void *)red_token))
		err(MALLOC, "push_hdoc", data, true);
	if (!vec_push(&group->input, (void *)fname_token))
		err(MALLOC, "push_hdoc", data, true);
	if (!vec_push(&data->exec->fname_vec, (void *)fname))
		err(MALLOC, "push_hdoc", data, true);
}

/**
 * @brief Creates a token for the hdoc file, and adds the filename to the f_name
 * @param	group the group to add the new token_vec to
 * @param	i to step over the heredoc and the quotes / filenames
 * @param	data general data struct
 * @param
 */
static void	hdoc_found(t_group *group, int *i, t_shell *data)
{
	t_token	*token;
	char	*stop;
	char	*filename;

	filename = ft_strjoin("./src/.heredoc/", ft_itoa((*i)));
	if (!filename)
		err(MALLOC, "hdoc_found", data, true);
	(*i) = +1;
	token = vec_get(&data->token_vec, (*i));
	if ((token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		&& ft_strlen(token->value) == 2)
		heredoc(filename, "", token->type, data);
	else
	{
		stop = rm_quotes(token);
		if (!stop)
			err(MALLOC, "hdoc_found", data, true);
		heredoc(filename, stop, token->type, data);
		free(stop);
	}
	push_hdoc(filename, group, data);
	(*i) += 1;
}

static void	group_tokens(t_group *group, int *i, t_shell *data)
{
	t_token	*dup;
	t_token	*token;

	token = (t_token *)vec_get(&data->token_vec, (*i));
	while (token->type != PIPE)
	{
		if (token->type == HEREDOC)
			hdoc_found(group, &i, data);
		else
		{
			dup = dup_token(token);
			if (!dup)
				err(MALLOC, "group_tokens", data, true);
			vec_push(&group->input, (void *)dup);
		}
		if ((*i) >= (&data->token_vec)->length)
			break ;
		(*i)++;
		token = (t_token *)vec_get(&data->exec->group_vec, (*i));
	}
	return (group);
}

/**
 * @brief Group the token_vec into groups
 *
 * @param token_vec The vector containing the token_vec
 * @return t_exec* The struct containing the groups
 */
void	group_token_vec(t_shell *data)
{
	size_t	i;
	t_exec	*exec;
	t_group	*group;

	data->exec = create_exec();
	if (!data->exec)
		err(MALLOC, "group_token_vec", data, true);
	i = 0;
	while (i < (&data->token_vec)->length)
	{
		group = create_group();
		if (!group)
			err(MALLOC, "group_token_vec", clear_exec, exec);
		group_tokens(group, &i, data);
		if (!vec_push(&exec->group_vec, group))
			err(MALLOC, "group_token_vec", data, true);
		i++;
	}
	return (exec);
}
