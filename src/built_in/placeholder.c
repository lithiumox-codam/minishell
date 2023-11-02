/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   placeholder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:46:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/02 21:02:04 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	char	**start;

	(void)group;
	env = combine_env(env_vec);
	start = env;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	ft_free(start);
	exit(0);
}
