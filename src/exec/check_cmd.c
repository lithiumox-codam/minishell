/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 17:36:19 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/09/11 20:02:03 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	process_path(t_group *group, char **paths)
{
	char	*tmp;
	char	*new_cmd;

	tmp = ft_strjoin(*paths, "/");
	if (tmp == NULL)
		exec_err("process_path", MALLOC);
	new_cmd = ft_strjoin(tmp, group->cmd);
	if (new_cmd == NULL)
		exec_err("process_path", MALLOC);
	free(tmp);
	if (access(new_cmd, F_OK) == 0)
	{
		if (access(new_cmd, X_OK) == -1)
			exec_err(group->cmd, PERMISSION);
		free(group->cmd);
		group->cmd = new_cmd;
		ft_free(paths);
		return (true);
	}
	free(new_cmd);
	return (false);
}

/**
 * @brief	Replaces the command with the correct path
*/
static void	replace_cmd(t_group *group, char *path)
{
	char	**paths;

	paths = ft_strsplit(path, ':');
	if (paths == NULL)
		exec_err("replace cmd", MALLOC);
	while (*paths != NULL)
	{
		if (process_path(group, paths))
			return ;
		paths++;
	}
	free(paths);
	exec_err(group->cmd, NOT_FOUND);
}

/**
 * @brief	checks if path is absolute, checks for permissions
 * @brief 	calls replace_cmd to find the correct path
 */
void	check_cmd(t_group *group)
{
	t_env	*env;
	size_t	i;

	if (group->cmd == NULL || group->cmd[0] == '\0')
		exec_err("", NOT_FOUND);
	if (access(group->cmd, F_OK) == 0)
		exec_absolute_path(group);
	i = 0;
	env = vec_get(&group->data->env, i);
	while (i < (&group->data->env)->length)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			break ;
		i++;
		env = vec_get(&group->data->env, i);
	}
	if (i == (&group->data->env)->length)
		exec_err(group->cmd, NO_SUCH);
	replace_cmd(group, env->value);
}
