/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 22:56:39 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/20 17:53:14 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

/**
 * @brief The main function of the unset built_in. It will loop through the
 * arguments and remove the corresponding environment variables from the
 * environment vector. (if they exist)
 *
 * @param group The group struct containing the arguments
 * @param env_vec The environment vector
 * @return void
 */
void	ft_unset(t_group *group, t_shell *data)
{
	size_t	i;
	size_t	index;
	t_env	*token;

	i = 1;
	while (group->args[i])
	{
		token = (t_env *)vec_find_f(&data->env, compare_env_key,
				group->args[i]);
		if (token)
		{
			index = (size_t)(token - (t_env *)(&data->env)->data);
			if (!vec_remove(&data->env, index))
			{
				exit_mini("ft_unset", 1);
				return ;
			}
		}
		i++;
	}
	data->error_type = NO_ERROR;
}
