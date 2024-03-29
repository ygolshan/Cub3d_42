/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:35:29 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:35:37 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}
