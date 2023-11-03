/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   placeholder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 14:46:00 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/03 18:45:31 by mdekker       ########   odam.nl         */
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
	size_t	i;

	(void)group;
	i = 0;
	while (i < env_vec->length)
	{
		printf("%s=%s\n", ((t_env *)vec_get(env_vec, i))->key,
			((t_env *)vec_get(env_vec, i))->value);
		i++;
	}
	exit(0);
}
