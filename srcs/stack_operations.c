/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:53:45 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:56:34 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	reverse_stack(t_node **stack)
{
	if ((*stack))
	{
		if ((*stack)->next == (*stack)->prev)
			(*stack) = (*stack)->next;
		else
			(*stack) = (*stack)->next;
	}
}

t_node	*copy_node(t_node *node)
{
	t_node	*temp;

	temp = new_(node->box, node->id);
	return (temp);
}

void	push_to_stack(t_node **from, t_node **to)
{
	t_node	*temp;

	if (*from)
	{
		temp = copy_node(*from);
		delete_head(from);
		add_head(to, temp);
	}
}

void	skipper(t_node **info, t_node **temp, t_node **fetched, char identifier)
{
	while ((*fetched)->box[0] != identifier)
	{
		reverse_stack(info);
		*fetched = *info;
	}
	push_to_stack(info, temp);
}

int	update_information(t_node **info, t_fetch *fetched)
{
	t_node	*temp;
	char	identifiers;

	identifiers = 'N';
	temp = NULL;
	fetched->p_t = *info;
	while (identifiers <= 'F')
	{
		skipper(info, &temp, &fetched->p_t, identifiers);
		identifiers++;
	}
	fetched->p_t = temp;
	fetched->len = 5;
	while (fetched->p_t && fetched->len--)
		push_to_stack(&temp, info);
	relist_nodes(info);
	return (1);
}
