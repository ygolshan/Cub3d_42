/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:04:06 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:56:17 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	configure_step(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir.y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

void	delta_dist(t_ray *ray)
{
	if (ray->ray_dir.y == 0)
	{
		ray->delta_dist.x = 0;
	}
	else
	{
		if (ray->ray_dir.x == 0)
			ray->delta_dist.x = 1;
		else
			ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	}
	if (ray->ray_dir.x == 0)
	{
		ray->delta_dist.y = 0;
	}
	else
	{
		if (ray->ray_dir.y == 0)
			ray->delta_dist.y = 1;
		else
			ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	}
}

void	calculate_side_distances(t_ray *ray, t_player pos)
{
	if (ray->ray_dir.x < 0)
		ray->side_dist.x = (pos.x - (double)ray->map_x) * ray->delta_dist.x;
	else
		ray->side_dist.x = (ray->map_x + 1.0 - pos.x) * ray->delta_dist.x;
	if (ray->ray_dir.y < 0)
		ray->side_dist.y = (pos.y - (double)ray->map_y) * ray->delta_dist.y;
	else
		ray->side_dist.y = (ray->map_y + 1.0 - pos.y) * ray->delta_dist.y;
}

t_ray	calculate_raycast(t_cub *cub, char **map, double camera_x)
{
	t_ray	ray;
	int		hit;

	hit = 0;
	configure_ray(cub, &ray, camera_x);
	while (hit == 0)
	{
		if (ray.side_dist.x < ray.side_dist.y)
			adjust_ray(&ray, 0);
		else if (ray.side_dist.x > ray.side_dist.y)
			adjust_ray(&ray, 1);
		else
		{
			adjust_ray(&ray, 0);
			adjust_ray(&ray, 1);
		}
		if (map[ray.map_y][ray.map_x] == '1')
			hit = 1;
	}
	set_perpendicular_distance(&ray, &cub->player_pos);
	return (ray);
}

void	configure_ray(t_cub *cub, t_ray *ray, double camera_x)
{
	ray->ray_dir.x = cub->player_pos.dirx + cub->player_pos.plane.x * camera_x;
	ray->ray_dir.y = cub->player_pos.diry + cub->player_pos.plane.y * camera_x;
	ray->map_x = (int)cub->player_pos.x;
	ray->map_y = (int)cub->player_pos.y;
	delta_dist(ray);
	configure_step(ray);
	calculate_side_distances(ray, cub->player_pos);
}
