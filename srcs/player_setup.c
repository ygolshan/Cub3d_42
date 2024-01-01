/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:03:12 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 13:28:21 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	set_player_plane_direction(t_cub *cub)
{
	if (cub->player_pos.dirx == 0)
	{
		if (cub->player_pos.diry == 1)
			cub->player_pos.plane.x = -1;
		else
			cub->player_pos.plane.x = 1;
		cub->player_pos.plane.y = 0;
	}
	else
	{
		if (cub->player_pos.dirx == 1)
			cub->player_pos.plane.y = 1;
		else
			cub->player_pos.plane.y = -1;
		cub->player_pos.plane.x = 0;
	}
	return ;
}

void	set_player_initial_position(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'S' || \
				cub->map[i][j] == 'W' || cub->map[i][j] == 'E')
			{
				cub->player_pos.x = (float)j + 0.5;
				cub->player_pos.y = (float)i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	set_player_orientation(t_cub *cub)
{
	if (cub->map[(int)cub->player_pos.y][(int)cub->player_pos.x] == 'N')
	{
		cub->player_pos.dirx = 0;
		cub->player_pos.diry = -1;
	}
	else if (cub->map[(int)cub->player_pos.y][(int)cub->player_pos.x] == 'S')
	{
		cub->player_pos.dirx = 0;
		cub->player_pos.diry = 1;
	}
	else if (cub->map[(int)cub->player_pos.y][(int)cub->player_pos.x] == 'W')
	{
		cub->player_pos.dirx = -1;
		cub->player_pos.diry = 0;
	}
	else if (cub->map[(int)cub->player_pos.y][(int)cub->player_pos.x] == 'E')
	{
		cub->player_pos.dirx = 1;
		cub->player_pos.diry = 0;
	}
	return ;
}

int	check_wall_collision(t_cub *cub, int key)
{
	t_cub		tmp;
	t_ray		ray;
	double		camera_x;
	int			x;

	tmp = *cub;
	adjust_player_position(&tmp, key);
	if (key == 124 || key == 123)
		adjust_player_rotation(&tmp, key, THREE_DEG);
	if (cub->map[(int)tmp.player_pos.y][(int)tmp.player_pos.x] == '1')
		return (1);
	set_player_plane_direction(&tmp);
	x = 0;
	while (x < WIN_SIZE_W)
	{
		camera_x = 2 * x / (double)WIN_SIZE_W - 1;
		ray = calculate_raycast(&tmp, tmp.map, camera_x);
		if (ray.perp_wall_dist < 0.3)
			return (1);
		x++;
	}
	return (0);
}

void	set_player_data(t_cub *cub)
{
	set_player_initial_position(cub);
	set_player_orientation(cub);
	set_player_plane_direction(cub);
	return ;
}
