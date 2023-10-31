/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/11 14:04:28 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/31 14:16:59 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @note	check if dup_fd or redirects should be done for the built_in
 */
void	exec_built_in(t_group *group, t_process type, t_vector *env_vec)
{
	dup_fd(group, type);
	if (is_special_builtin(group->cmd))
		exit(0);
	if (ft_strcmp(group->cmd, "echo") == 0)
		ft_echo(group);
	else if (ft_strcmp(group->cmd, "pwd") == 0)
		ft_pwd(group);
	else if (ft_strcmp(group->cmd, "env") == 0)
		ft_env(group, env_vec);
}

void	exec_special_builtin(t_group *group, t_shell *data)
{
	if (ft_strcmp(group->cmd, "exit") == 0)
		ft_exit(group, data);
	else if (ft_strcmp(group->cmd, "cd") == 0)
		ft_cd(group);
	else if (ft_strcmp(group->cmd, "export") == 0)
		ft_export(group, &data->env);
	else if (ft_strcmp(group->cmd, "unset") == 0)
		ft_unset(group, &data->env);
}
