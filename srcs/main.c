/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhodara <akhodara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:54:54 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 17:48:15 by akhodara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	start_game(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	render_game_screen(cub);
	render_minimap(cub);
	render_player(cub);
	return ;
}

int	window_close_event(t_cub *cub)
{
	close_and_free_resources(cub, "Window closed by user");
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (1);
	if (!game_init(&cub))
		close_and_free_resources(&cub, "Error\n");
	if (!parser(validate_map_file(argv[1]), &cub))
	{
		exit(printf("invalid\n"));
	}
	setup_graphic(&cub.graphic_info, &cub);
	load_images(&cub);
	set_player_data(&cub);
	start_game(&cub);
	mlx_hook(cub.win, 2, 0, move, &cub);
	mlx_hook(cub.win, 3, 0, end_key_motion, &cub);
	mlx_hook(cub.win, 17, 0, window_close_event, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

void	adjust_ray(t_ray *ray, int axis)
{
	if (axis == 0)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
	}
	ray->side = axis;
}

void	set_perpendicular_distance(t_ray *ray, t_player *pos)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - pos->x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - pos->y + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir.y;
}
