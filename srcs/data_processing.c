/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:01:50 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/24 16:24:25 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

char	*process_line_spaces(char *box)
{
	int		i;
	int		flag;
	char	*out;

	i = 0;
	flag = 0;
	out = malloc(1);
	out[0] = 0;
	while (box[i])
	{
		if (ft_isspace(box[i]) && flag == 0)
		{
			flag = 1;
			ft_cpychar(box[i], &out);
		}
		else if (ft_isspace(box[i]) && flag == 1)
		{
			i++;
			continue ;
		}
		else
			ft_cpychar(box[i], &out);
		i++;
	}
	return (out);
}

int	adjust_info_data(t_node **info, t_fetch *fetched)
{
	char	*temp;

	fetched->p_t = *info;
	fetched->len = MAX_MAP_PARAMS;
	while (fetched->p_t && fetched->len--)
	{
		temp = process_line_spaces(fetched->p_t->box);
		free(fetched->p_t->box);
		fetched->p_t->box = NULL;
		fetched->p_t->box = ft_strdup(temp);
		free(temp);
		temp = NULL;
		fetched->p_t = fetched->p_t->next;
	}
	return (1);
}

int	check_box_equality(int *i, t_node *p_checks, char *temp)
{
	if (!ft_strcmp(temp, p_checks->box))
	{
		if (p_checks->status == 0)
		{
			p_checks->status = 1;
			(*i)++;
		}
		else
			return (0);
	}
	return (1);
}

void	create_compare_string(char *temp, char *box)
{
	temp[0] = box[0];
	temp[1] = box[1];
	temp[2] = '\0';
}

int	check_data_presence(t_node *info, t_fetch *fetched)
{
	t_node	*p_checks;
	int		checks_len;
	char	temp[3];
	int		i;

	fetched->p_t = info;
	fetched->len = 6;
	p_checks = fetched->checks;
	i = 0;
	while (fetched->p_t && fetched->len--)
	{
		create_compare_string(temp, fetched->p_t->box);
		checks_len = 6;
		while (p_checks && checks_len--)
		{
			if (check_box_equality(&i, p_checks, temp))
				p_checks = p_checks->next;
			else
				return (0);
		}
		fetched->p_t = fetched->p_t->next;
	}
	return (i);
}
