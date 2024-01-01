/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:27:33 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:27:42 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	i;

	if (!s1)
		return ((void *) 0);
	ret = ft_calloc(sizeof(*s1), (ft_strlen(s1) + 1));
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	return (ret);
}
