/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:45 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:08:15 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	add_head(t_node **head, t_node *newnode)
{
	t_node	*tail;

	if (*head == NULL)
	{
		*head = newnode;
		newnode->next = newnode;
		newnode->prev = newnode;
	}
	else
	{
		tail = (*head)->prev;
		newnode->prev = tail;
		newnode->next = *head;
		tail->next = newnode;
		(*head)->prev = newnode;
		*head = newnode;
	}
}

void	add_tail(t_node **head, t_node *newnode)
{
	t_node	*tail;

	if (*head == NULL)
	{
		*head = newnode;
		newnode->next = newnode;
		newnode->prev = newnode;
	}
	else
	{
		tail = (*head)->prev;
		newnode->prev = tail;
		newnode->next = *head;
		tail->next = newnode;
		(*head)->prev = newnode;
	}
}

void	delete_head(t_node **head)
{
	t_node	*current;
	t_node	*newhead;

	if (*head == NULL)
		return ;
	current = *head;
	if (current->next == current)
	{
		free(current->box);
		free(current);
		*head = NULL;
	}
	else
	{
		newhead = current->next;
		newhead->prev = current->prev;
		current->prev->next = newhead;
		free(current->box);
		free(current);
		*head = newhead;
	}
}

void	delete_tail(t_node **head)
{
	t_node	*tail;
	t_node	*newtail;

	if (*head == NULL)
		return ;
	tail = (*head)->prev;
	if (*head == tail)
	{
		free(*head);
		*head = NULL;
	}
	else
	{
		newtail = tail->prev;
		newtail->next = *head;
		(*head)->prev = newtail;
		free(tail);
	}
}

t_node	*matrix_to_list(char **matrix)
{
	t_node	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (matrix[i])
		add_tail(&temp, new_((matrix[i++]), 0));
	relist_nodes(&temp);
	return (temp);
}
