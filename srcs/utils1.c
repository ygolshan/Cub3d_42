/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:25 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/24 18:07:50 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	free_content(t_node	*h)
{
	t_node	*temp;
	int		len;

	if (h)
	{
		len = h->prev->id;
		temp = h;
		while (temp && len--)
		{
			free(temp->box);
			temp->box = NULL;
			temp = temp->next;
		}
	}
}

void	free_list(t_node **h)
{
	while ((*h))
		delete_tail(h);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (&str[i]);
			++j;
		}
		++i;
	}
	return (0);
}

t_node	*new_(char *content, int id)
{
	t_node	*temp;

	temp = malloc(sizeof(t_node));
	temp->id = id;
	temp->status = 0;
	temp->box = ft_strdup(content);
	temp->type = NULL;
	temp->next = temp;
	temp->prev = temp;
	return (temp);
}

void	relist_nodes(t_node **h)
{
	t_node	*tmp;
	int		i;

	if (*h)
	{
		i = 0;
		tmp = (*h);
		while (tmp->next != *h && ++i)
		{
			tmp->id = i;
			tmp = tmp->next;
		}
		tmp->id = ++i;
	}
}
