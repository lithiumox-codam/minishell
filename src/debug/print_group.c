/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_group.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 13:57:39 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/10/03 17:56:11 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void print_array(char **array)
{
	size_t	i;

	i = 0;
	printf("\n");
	if (!array)
	{
		printf("NULL\n");
		return ;
	}
	while (array[i])
	{
		printf("[%zu]:%s\n", i, array[i]);
		i++;
	}
	printf("\n");
}

void p_group(t_group *group)
{
		printf("----- Printing Group Details -----\n");
		printf("Command: %s\n", group->cmd);
		printf("Arguments: ");
		print_array(group->args);
		printf("Input Redirection: ");
		print_vector(&group->in_red, print_token);
		printf("\n");
		printf("Output Redirection: ");
		print_vector(&group->out_red, print_token);
		printf("\n");
		printf("Left Pipe[0]: %d\n", group->left_pipe[0]);
		printf("Left Pipe[1]: %d\n", group->left_pipe[1]);
		printf("Right Pipe[0]: %d\n", group->right_pipe[0]);
		printf("Right Pipe[1]: %d\n", group->right_pipe[1]);
		printf("Process ID: %d\n", group->pd);
		printf("----- End of Group Details -----\n");
}

void print_group(t_shell *data)
{
	t_group	*group;
	size_t	i;

	i = 0;
	while (i < data->exec->group_vec.length)
	{
		group = (t_group *)vec_get(&data->exec->group_vec, i);
		printf("group %zu\n", i);
		p_group(group);
		i++;
	}
}
