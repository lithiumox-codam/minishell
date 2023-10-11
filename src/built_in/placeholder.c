/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   placeholder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:46:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/04 16:50:58 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(t_group *group)
{
	size_t	i;

	i = 1;
	while (group->args[i])
	{
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
	(void)group;
	printf("built_in pwd placeholder\n");
	exit(0);
}

void	ft_env(t_group *group)
{
	(void)group;
	printf("built_in env placeholder\n");
	exit(0);
}
