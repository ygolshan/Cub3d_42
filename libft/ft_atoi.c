/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:36:19 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:36:21 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	base(int c, int base)
{
	int	i;

	i = 0;
	while (i < base)
	{
		if (c == "0123456789abcdef"[i] || c == "0123456789ABCDEF"[i])
			return (i);
		i++;
	}
	return (-1);
}

int	check_sign(char sign)
{
	if (sign > '9' || sign < '0')
		return (0);
	return (1);
}

long long	a_(char *str, int len_base)
{
	int			i;
	long long	nbr;
	int			sig;

	i = 0;
	nbr = 0;
	sig = 1;
	if (str[i] == '-')
	{
		sig = -1;
		i++;
	}
	if (str[i] == '+')
	{
		sig = 1;
		i++;
	}
	while (base(str[i], len_base) != -1)
	{
		nbr = nbr * len_base;
		nbr = nbr + base(str[i], len_base);
		i++;
	}
	return ((long long)(nbr * sig));
}
