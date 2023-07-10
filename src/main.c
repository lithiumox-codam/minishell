/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/10 10:10:41 by mdekker       #+#    #+#                 */
/*   Updated: 2023/07/10 10:23:56 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	for (int i = 0; env[i]; i++)
		printf("%s\n", env[i]);
	return (0);
}
