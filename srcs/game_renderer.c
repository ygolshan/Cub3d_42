/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:51:24 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 13:16:31 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

t_render_info	render_info(t_ray *ray, t_player *player)
{
	t_render_info	render_info;

	render_info.line_height = (int)(WIN_SIZE_H / ray->perp_wall_dist);
	render_info.ratio = (double)TILE_SIZE / render_info.line_height;
	render_info.start_y = (WIN_SIZE_H / 2) - (render_info.line_height / 2);
	render_info.end_y = (WIN_SIZE_H / 2) + (render_info.line_height / 2);
	if (render_info.start_y < 0)
		render_info.start_y = 0;
	if (render_info.end_y >= WIN_SIZE_H)
		render_info.end_y = WIN_SIZE_H;
	render_info.tex_x = calculate_texture_x(player, ray);
	render_info.tex_pos = (render_info.start_y - WIN_SIZE_H / 2
			+ render_info.line_height / 2) * render_info.ratio;
	return (render_info);
}

void	render_wall_segment(t_cub *cub, t_ray *ray, int x)
{
	t_render_info	info;
	t_img_info		*tex_info;
	t_img_info		*img_info;
	int				color;

	img_info = &cub->graphic_info.img_info;
	info = render_info(ray, &cub->player_pos);
	tex_info = cub->graphic_info.texture_info;
	while (info.start_y < info.end_y)
	{
		info.tex_y = (int)info.tex_pos & (TILE_SIZE - 1);
		if (ray->side == 0 && ray->ray_dir.x > 0)
			color = get_img_pixel_color(&tex_info[0], info.tex_x, info.tex_y);
		else if (ray->side == 0 && ray->ray_dir.x < 0)
			color = get_img_pixel_color(&tex_info[1], info.tex_x, info.tex_y);
		else if (ray->side == 1 && ray->ray_dir.y > 0)
			color = get_img_pixel_color(&tex_info[2], info.tex_x, info.tex_y);
		else if (ray->side == 1 && ray->ray_dir.y < 0)
			color = get_img_pixel_color(&tex_info[3], info.tex_x, info.tex_y);
		draw_safe_pixel(img_info, x, info.start_y, color);
		my_mlx_pixel_put(cub->data, x, info.start_y, color);
		info.tex_pos += info.ratio;
		info.start_y++;
	}
}

void	render_game_background(t_cub *cub)
{
	int			x;
	int			y;

	y = -1;
	while (++y < WIN_SIZE_H / 2)
	{
		x = -1;
		while (++x < WIN_SIZE_W)
		{
			my_mlx_pixel_put(cub->data, x, y, cub->ceil_color);
			my_mlx_pixel_put(cub->data, x, y + (WIN_SIZE_H / 2),
				cub->floor_color);
		}
	}
}

void	render_game_screen(t_cub *cub)
{
	int		x;
	t_ray	ray;
	double	camera_x;

	x = 0;
	render_game_background(cub);
	while (x < WIN_SIZE_W)
	{
		camera_x = 2 * x / (double)WIN_SIZE_W - 1;
		ray = calculate_raycast(cub, cub->map, camera_x);
		render_wall_segment(cub, &ray, x);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->data->img, 0, 0);
}

int	count_rows_in_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix[i])
		i++;
	return (i);
}
