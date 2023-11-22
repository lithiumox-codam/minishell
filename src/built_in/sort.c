/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker <mdekker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:43:05 by mdekker       #+#    #+#                 */
/*   Updated: 2023/11/21 18:22:54 by mdekker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief A function to compare two keys of the env vector
 *
 * @param index1 The index of the first key
 * @param index2 The index of the second key
 * @param enn The vector containing the keys
 * @return int The result of the comparison
 */
static int	compare_keys(size_t index1, size_t index2, t_vector *env)
{
	return (ft_strcmp(((t_env *)vec_get(env, index1))->key,
			((t_env *)vec_get(env, index2))->key));
}

/**
 * @brief Quick and dirty bubble sort for size_t arrays
 *
 * @param arr The array to sort
 * @param len The length of the array (same as the env vector)
 * @param env The environment vector
 */
void	bubble_sort(size_t **arr, size_t len, t_vector *env)
{
	size_t	i;
	size_t	j;
	size_t	*temp;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (compare_keys(*arr[j], *arr[j + 1], env) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief A function to free a size_t array
 *
 * @param arr The array to free
 * @param len The length of the array
 */
void	ft_free_size_t(size_t **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Return a sorted set of size_t indexes of the env vector
 *
 * @param env The vector to sort
 * @return size_t** The sorted set of indexes
 */
size_t	**return_sorted_arr(t_vector *env)
{
	size_t	**sorted_arr;
	size_t	i;

	i = 0;
	sorted_arr = malloc(sizeof(size_t *) * (env->length + 1));
	while (i < env->length)
	{
		sorted_arr[i] = malloc(sizeof(size_t));
		if (!sorted_arr[i])
		{
			ft_free_size_t(sorted_arr, i);
			return (NULL);
		}
		*sorted_arr[i] = i;
		i++;
	}
	sorted_arr[i] = NULL;
	bubble_sort(sorted_arr, env->length, env);
	return (sorted_arr);
}
