/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 10:10:41 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/10 11:58:12 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
	return (0);
}
