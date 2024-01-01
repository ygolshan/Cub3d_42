/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:07:41 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:45:10 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	validate_rgb_format(char *box)
{
	int	i;

	i = 1;
	while (box[++i])
		if (!ft_isdigit(box[i]) && box[i] != ',')
			return (0);
	return (1);
}

int	control(int x)
{
	return (x >= 0 && x <= 255);
}

int	fetch_rgb_value(t_cub **cub, char c[4], int nvalue, int i)
{
	if (nvalue == 1)
		(*cub)->colorr.r = a_(c, 10);
	if (nvalue == 2)
		(*cub)->colorr.g = a_(c, 10);
	if (nvalue == 3)
	{
		(*cub)->colorr.b = a_(c, 10);
		if (i == 6)
			(*cub)->floor_color = (*cub)->colorr.r << 16
				| (*cub)->colorr.g << 8 | (*cub)->colorr.b;
		else
			(*cub)->ceil_color = (*cub)->colorr.r << 16
				| (*cub)->colorr.g << 8 | (*cub)->colorr.b;
	}
	if (!control((*cub)->colorr.r) || !control((*cub)->colorr.g)
		|| !control((*cub)->colorr.b))
		return (0);
	return (1);
}

int	build_rgb_value(char *box, int *k, int *h, char c[4])
{
	ft_memset(c, 0, ft_strlen(c));
	*h = 0;
	while (ft_isdigit(box[(*k)]))
	{
		if (*h > 2)
			return (0);
		c[*h] = box[(*k)++];
		(*h)++;
	}
	c[*h] = 0;
	return (1);
}

int	skip_non_digit_characters(char *box, int *k, int *nvalue)
{
	int	digitfound;

	digitfound = 0;
	while (box[*k] != '\0')
	{
		if (!ft_isdigit(box[*k]))
			(*k)++;
		else
		{
			digitfound = 1;
			break ;
		}
	}
	if (digitfound)
	{
		(*nvalue)++;
		return (1);
	}
	return (0);
}
