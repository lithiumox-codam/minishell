/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   placeholder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:46:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/26 15:15:53 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_group *group)
{
	size_t	i;

	i = 1;
	while (group->args[i])
	{
		printf("Triggered exho built in\n");
		write(1, group->args[i], ft_strlen(group->args[i]));
		if (group->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	exit(0);
}

void	ft_pwd(t_group *group)
{
	char	buff[1024];

	(void)group;
	getcwd(buff, 1024);
	printf("%s\n", buff);
	exit(0);
}

void	ft_env(t_group *group, t_vector *env_vec)
{
	char	**env;

	(void)group;
	env = combine_env(env_vec);
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	exit(0);
}
