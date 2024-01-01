/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:00:38 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 10:31:54 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	check_first_and_last_wall(char *box, int *k)
{
	(*k) = 0;
	if (box[0] == '1' && box[ft_strlen(box) - 1] == '1')
		return (1);
	return (0);
}

int	check_wall_row(char *box)
{
	int	i;

	i = -1;
	while (box[++i])
		if (box[i] != '1' && box[i] != ' ')
			return (0);
	return (1);
}

int	valid_char(char c)
{
	if (c != '1'
		&& c != '0'
		&& c != ' '
		&& c != 'N'
		&& c != 'S'
		&& c != 'E'
		&& c != 'W')
		return (0);
	return (1);
}

void	ft_cpychar(char c, char **out)
{
	char	c_[2];

	c_[0] = c;
	c_[1] = '\0';
	*out = ft_strjoin(*out, c_);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
