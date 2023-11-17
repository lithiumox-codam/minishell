/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 22:56:39 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/11/17 01:17:28 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_signal	g_signal;

/**
 * @brief The main function of the unset built_in. It will loop through the
 * arguments and remove the corresponding environment variables from the
 * environment vector.
 *
 * @param group The group struct containing the arguments
 * @param env_vec The environment vector
 * @return void
 * @note The exit status will be set to 1 if an error occurs
 */
void	ft_unset(t_group *group, t_vector *env_vec)
{
	size_t i;
	size_t index;
	t_env *token;

	i = 1;
	while (group->args[i])
	{
		token = (t_env *)vec_find_f(env_vec, compare_env_key, group->args[i]);
		if (token)
		{
			index = (size_t)(token - (t_env *)env_vec->data);
			if (!vec_remove(env_vec, index))
			{
				g_signal.exit_status = 1;
				return ;
			}
		}
		else
		{
			g_signal.exit_status = 1;
			return ;
		}
		i++;
	}
	g_signal.exit_status = 0;
}