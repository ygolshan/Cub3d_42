/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:34:32 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:34:41 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*i;

	if (!b)
		return (NULL);
	i = b;
	while (len > 0)
	{
		*i++ = (unsigned char)c;
		len--;
	}
	return (b);
}
