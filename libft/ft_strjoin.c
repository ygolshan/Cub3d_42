/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhodara <akhodara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:27:23 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 17:47:27 by akhodara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*sum;

	sum = malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sum)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		sum[i++] = s1[j++];
	j = 0;
	while (s2[j])
		sum[i++] = s2[j++];
	sum[i] = '\0';
	free((char *)s1);
	return (sum);
}
