/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/30 23:47:46 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Creates a token for the hdoc file, and adds the filename to the f_name
 * @param	token_vec the token vector
 * @param	group the group to add the new tokens to
 * @param	i to step over the heredoc and the quotes / filenames
 * @param
 */
bool	hdoc_found(t_vector token_vec, t_group *group, int *i,
		t_vector fname_vec)
{
	t_token	*token;
	t_exec	*exec;
	char	*stop;
	char	*filename;
	char	*fname;

	filename = ft_strjoin("./src/.heredoc/", ft_itoa((*i)));
	if (!filename)
		return (false); // strerror malloc + set exitstatus?
	(*i) = +1;
	token = vec_get(&token_vec, (*i));
	if ((token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		&& ft_strlen(token->value) == 2)
		heredoc(filename, "", token->type);
	else
	{
		stop = rm_quotes(token);
		if (!stop)
			return (false); // malloc error
		heredoc(filename, stop, token->type);	
		free(stop);
	}
	fname = ft_strdup(filename);
	if (!fname)
		return (false); // malloc serror
	token = create_token(filename, HEREDOC);
	if (!token)
		return (false); // malloc error
	if (!vec_push(&group->input, (void *)token))
		return (false); // malloc error
	if (!vec_push(&fname_vec, (void *)fname))
		return (false); // malloc error
	(*i) += 1;
	return (true);
}

t_group *make_group(t_vector *token_vec, int *i, t_exec *exec)
{
	t_token		*dup;
	t_group		*group;
	t_token		*token;

	group = create_group();
	if (!group)
		err(MALLOC, NULL, clear_exec, exec);
	token = (t_token *)vec_get(token_vec, (*i));
	while (token->type != PIPE)
	{
		if (token->type == HEREDOC)
			hdoc_found(*token_vec, group, i, exec->fname_vec);
		else
		{
			dup = dup_token(token);
			if (!dup)
				err(MALLOC, NULL, clear_exec, exec);
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
	size_t		i;
	t_exec		*exec;
	t_vector	group_vec;
	t_group		*group;

	exec = create_exec();
	if (!exec)
		err(MALLOC, 0, 0, 0);
	i = 0;
	while (i < token_vec->length)
	{
		group = make_group(token_vec, &i, exec);
		vec_push(&group_vec, group);
		i++;
	}
	exec->envp = envp;
	return (exec);
}
