/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 17:36:19 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/12 20:15:51 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static bool	process_path(t_group *group, char **paths, int i)
{
	char	*tmp;
	char	*new_cmd;

	tmp = ft_strjoin(paths[i], "/");
	if (tmp == NULL)
		exec_err("process_path", MALLOC);
	new_cmd = ft_strjoin(tmp, group->cmd);
	if (new_cmd == NULL)
		exec_err("process_path", MALLOC);
	free(tmp);
	if (access(new_cmd, F_OK) == 0)
	{
		if (access(new_cmd, X_OK) != 0)
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
 * @brief	Checks if the command is in the path
 * @details if it is, it replaces the command with the full path
 * @details if it is not, it calls exec_err
 */
static void	find_cmd_path(t_group *group, char *path)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	if (paths == NULL)
		exec_err("replace cmd", MALLOC);
	while (paths[i] != NULL)
	{
		if (process_path(group, paths, i))
			return ;
		i++;
	}
	ft_free(paths);
	exec_err(group->cmd, NOT_FOUND);
}

/**
 * @brief	checks if path is absolute, checks for permissions
 * @brief 	calls replace_cmd to find the correct path
 */
void	check_cmd(t_group *group, t_process type, t_vector *env_vec)
{
	t_env	*env;
	size_t	i;

	if (group->cmd == NULL || group->cmd[0] == '\0')
		exec_err("", NOT_FOUND);
	if (access(group->cmd, F_OK) == 0)
		exec_absolute_path(group, type, env_vec);
	i = 0;
	while (i < env_vec->length)
	{
		env = vec_get(env_vec, i);
		if (ft_strcmp(env->key, "PATH") == 0)
			break ;
		i++;
	}
	if (i == env_vec->length)
		exec_err(group->cmd, NO_SUCH);
	find_cmd_path(group, env->value);
}
