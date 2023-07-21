/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   global.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 04:17:23 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/21 12:51:05 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_data;

/**
 * @brief Frees the global variables
 *
 * @param exit If is true, the exit status and env vector will be freed
 */
void	free_global(bool exit)
{
	ft_vec_free(&g_data.tokens);
	if (exit)
	{
		ft_vec_free(&g_data.env);
		free(g_data.exit_status);
	}
}