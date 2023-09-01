/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/01 20:49:26 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	push_hdoc(char *filename, t_group *group, t_exec *exec)
{
	char	*fname;
	t_token	*red_token;
	t_token	*fname_token;

	fname = ft_strdup(filename);
	if (!fname)
		err(MALLOC, "push_hdoc", clear_exec, exec);
	fname_token = create_token(filename, STRING);
	if (!fname_token)
		err(MALLOC, "push_hdoc", clear_exec, exec);
	red_token = create_token("<", I_REDIRECT);
	if (!red_token)
		err(MALLOC, "push_hdoc", clear_exec, exec);
	if (!vec_push(&group->input, (void *)red_token))
		err(MALLOC, "push_hdoc", clear_exec, exec);
	if (!vec_push(&group->input, (void *)fname_token))
		err(MALLOC, "push_hdoc", clear_exec, exec);
	if (!vec_push(&exec->fname_vec, (void *)fname))
		err(MALLOC, "push_hdoc", clear_exec, exec);
}

/**
 * @brief Creates a token for the hdoc file, and adds the filename to the f_name
 * @param	token_vec the token vector
 * @param	group the group to add the new tokens to
 * @param	i to step over the heredoc and the quotes / filenames
 * @param
 */
static void	hdoc_found(t_vector token_vec, t_group *group, int *i, t_exec *exec)
{
	t_token	*token;
	char	*stop;
	char	*filename;

	filename = ft_strjoin("./src/.heredoc/", ft_itoa((*i)));
	if (!filename)
		err(MALLOC, "hdoc_found", clear_exec, exec);
	(*i) = +1;
	token = vec_get(&token_vec, (*i));
	if ((token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		&& ft_strlen(token->value) == 2)
		heredoc(filename, "", token->type, exec);
	else
	{
		stop = rm_quotes(token);
		if (!stop)
			err(MALLOC, "hdoc_found", clear_exec, exec);
		heredoc(filename, stop, token->type, exec);
		free(stop);
	}
	push_hdoc(filename, group, exec);
	(*i) += 1;
}

t_group	*make_group(t_vector *token_vec, int *i, t_exec *exec)
{
	t_token	*dup;
	t_group	*group;
	t_token	*token;

	group = create_group();
	if (!group)
		err(MALLOC, "make_group", clear_exec, exec);
	token = (t_token *)vec_get(token_vec, (*i));
	while (token->type != PIPE)
	{
		if (token->type == HEREDOC)
			hdoc_found(*token_vec, group, i, exec);
		else
		{
			dup = dup_token(token);
			if (!dup)
				err(MALLOC, "make_group", clear_exec, exec);
			vec_push(&group->input, (void *)dup);
		}
		if ((*i) >= token_vec->length)
			break ;
		(*i)++;
		token = (t_token *)vec_get(token_vec, (*i));
	}
	return (group);
}

/**
 * @brief Group the tokens into groups
 *
 * @param token_vec The vector containing the tokens
 * @return t_exec* The struct containing the groups
 */
t_exec	*group_tokens(t_vector *token_vec, char **envp)
{
	size_t	i;
	t_exec	*exec;
	t_group	*group;

	exec = create_exec();
	if (!exec)
		err(MALLOC, "group_tokens", NULL, NULL);
	i = 0;
	while (i < token_vec->length)
	{
		group = make_group(token_vec, &i, exec);
		vec_push(&exec->group_vec, group);
		i++;
	}
	return (exec);
}
