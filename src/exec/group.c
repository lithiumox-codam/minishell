/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 19:55:05 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/08/28 11:25:54 by mdekker       ########   odam.nl         */
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

	filename = ft_strjoin("./src/.heredoc/", ft_itoa((int *)(*i)));
	if (!filename)
		return (false); // strerror malloc + set exitstatus?
	(*i) = +1;
	token = ft_vec_get(&token_vec, (*i));
	if ((token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		&& ft_strlen(token->value) == 2)
	{
		if (heredoc(filename, "", token->type))
			return (false); // hdoc error -> error code written in hdoc
	}
	else
	{
		stop = rm_quotes(token);
		if (!stop)
			return (false); // malloc error
		if (heredoc(filename, stop, token->type))
			return (false); // hdoc error -> error code written in hdoc
		free(stop);
	}
	fname = ft_strdup(filename);
	if (!fname)
		return (false); // malloc serror
	if ((&group->input)->length == 0)
		token = create_token(filename, I_REDIRECT);
	else
		token = create_token(filename, STRING);
	if (!token)
		return (false); // malloc error
	if (!ft_vec_push(&group->input, (void *)token))
		return (false); // malloc error
	if (!ft_vec_push(&fname_vec, fname))
		return (false); // malloc error
	(*i) += 1;
	return (true);
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
	t_token		*token;

	exec = create_exec();
	if (!exec)
		return (NULL);
	i = 0;
	while (i < token_vec->length)
	{
		group = create_group();
		if (!group)
			return (ft_vec_free(&group_vec), NULL);
		token = (t_token *)ft_vec_get(token_vec, i);
		while (token->type != PIPE)
		{
			if (token->type == HEREDOC)
				hdoc_found(*token_vec, group, &i, exec->fname_vec);
			else
				ft_vec_push(&group->input, (void *)dup_token(&token_vec,
						token));
			if (i >= token_vec->length)
				break ;
			i++;
			token = (t_token *)ft_vec_get(token_vec, i);
		}
		ft_vec_push(&group_vec, group); // push the created group
		if (i >= token_vec->length)
			break ;
		i++;
	}
	exec->envp = envp;
	// verify that groups only have redirects / heredocs at ends
	return (exec);
}
