/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdekker/jde-baai <team@codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/13 17:36:56 by mdekker/jde   #+#    #+#                 */
/*   Updated: 2023/07/13 17:45:08 by mdekker/jde   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * @brief Creates a new node
 *
 * @param value value to put in node
 * @return t_token* pointer to new node
 */
static t_token	*create_node(char *str, t_types type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = str;
	new->type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/**
 * @brief links two nodes
 *
 * @param node node to link to
 * @param newnode node to link
 * @return t_token* pointer to HEAD
 */
static t_token	*link_node(t_token *node, t_token *newnode)
{
	if (node == NULL || newnode == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	newnode->prev = node;
	node->next = newnode;
	return (newnode);
}

/**
 * @brief Append a node to the list or create a new list
 *
 * @param head Pointer to the head of the list or NULL
 * @param str String to put in the node
 * @return t_token* The head of the list
 */
t_token	*list_append(t_token *head, char *str, t_types type)
{
	t_token	*new;

	if (head == NULL)
	{
		head = create_node(str, type);
		if (head == NULL)
			return (NULL);
	}
	else
	{
		new = create_node(str, type);
		if (new == NULL)
			return (NULL);
		if (link_node(head, new) == NULL)
			return (NULL);
	}
	return (head);
}

/**
 * @brief Insert a node at a given index
 *
 * @param head The list to insert in
 * @param str The string to put in the node
 * @param type The type of the node
 * @param index The index to insert at
 * @return t_token* The head of the list
 */
t_token	*list_insert(t_token *head, char *str, t_types type, size_t index)
{
	t_token	*new;
	t_token	*tmp;
	size_t	i;

	new = create_node(str, type);
	if (new == NULL)
		return (NULL);
	tmp = head;
	i = 0;
	while (i < index && tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	new->next = tmp->next;
	new->prev = tmp;
	tmp->next = new;
	return (head);
}
