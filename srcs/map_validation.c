/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:55:40 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 12:10:09 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	is_void(char **map, int i, int k)
{
	if (map[i - 1][k] == ' ' || !map[i - 1][k]
		|| map[i + 1][k] == ' ' || !map[i + 1][k]
		|| map[i][k - 1] == ' ' || !map[i][k - 1]
		|| map[i][k + 1] == ' ' || !map[i][k + 1])
		return (1);
	return (0);
}

int	is_player(t_cub **cub, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*cub)->player_existence++;
		return (1);
	}
	return (0);
}

int	standard_map(t_cub **cub)
{
	char	*to_normalize;
	int		len;
	int		temp;
	t_node	*map_;

	map_ = (*cub)->fetched->map;
	len = (*cub)->fetched->map->prev->id;
	while (map_ && len--)
	{
		temp = (*cub)->fetched->len - ft_strlen(map_->box);
		to_normalize = malloc(temp);
		ft_memset(to_normalize, '0', temp);
		to_normalize[temp] = 0;
		map_->box = ft_strjoin(map_->box, to_normalize);
		free(to_normalize);
		map_ = map_->next;
	}
	(*cub)->map = node_list_to_matrix(&(*cub)->fetched->map);
	return (1);
}

int	map_checks(t_cub **cub, int i)
{
	int	k;

	k = 0;
	while ((*cub)->fetched->map_mtx[++i])
	{
		if (check_first_and_last_wall((*cub)->fetched->map_mtx[i], &k))
		{
			while ((*cub)->fetched->map_mtx[i][++(k)])
				if ((*cub)->fetched->map_mtx[i][(k)] == '0'
				|| is_player(cub, (*cub)->fetched->map_mtx[i][(k)]))
					if (is_void((*cub)->fetched->map_mtx, i, (k)))
						return (0);
		}
		else
			return (0);
	}
	if ((*cub)->player_existence == 1)
	{
		free_content((*cub)->fetched->map);
		free_list(&(*cub)->fetched->map);
		(*cub)->fetched->map = matrix_to_list((*cub)->fetched->map_mtx);
		return (1);
	}
	return (0);
}

int	validate_map(t_cub **cub)
{
	int	i;
	int	len;

	(*cub)->fetched->p_t = (*cub)->fetched->map;
	len = (*cub)->fetched->map->prev->id;
	while ((*cub)->fetched->p_t && len--)
	{
		i = -1;
		while ((*cub)->fetched->p_t->box[++i])
			if (!valid_char((*cub)->fetched->p_t->box[i]))
				return (0);
		(*cub)->fetched->p_t = (*cub)->fetched->p_t->next;
	}
	(*cub)->fetched->map_mtx = node_list_to_matrix(&(*cub)->fetched->map);
	return (1);
}
