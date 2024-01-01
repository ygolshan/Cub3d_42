/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhodara <akhodara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:51:16 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 17:47:56 by akhodara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	close_and_free_resources(t_cub *cub, char *mex)
{
	int	i;

	if (!cub->mlx || !cub->win)
	{
		exit(1);
	}
	mlx_destroy_window(cub->mlx, cub->win);
	if (cub->str_tmp)
		free(cub->str_tmp);
	if (!cub->data)
	{
		exit(1);
	}
	free(cub->data);
	i = 0;
	while (i < 4)
	{
		if (cub->wall_imgs_addrs[i])
			free(cub->wall_imgs_addrs[i]);
		i++;
	}
	fprintf(stderr, "Quitting Cube: %s", mex);
	exit(0);
}

int	exit_hook(t_cub *cub)
{
	close_and_free_resources(cub, "Closed program");
	return (0);
}

unsigned int	get_img_pixel_color(t_img_info *img_info, int x, int y)
{
	int	color_byte;
	int	pixel;

	color_byte = img_info->bpp / 8;
	pixel = (y * img_info->size_line) / color_byte + x;
	return (*(img_info->buf + pixel));
}

int	calculate_texture_x(t_player *player, t_ray *ray)
{
	double	wall_x;
	int		texture_x;

	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir.x;
	wall_x = wall_x - floor(wall_x);
	texture_x = (int)(wall_x * (double)TILE_SIZE);
	if ((ray->side == 0 && ray->ray_dir.x < 0)
		|| (ray->side == 1 && ray->ray_dir.y > 0))
		texture_x = TILE_SIZE - texture_x - 1;
	return (texture_x);
}

void	draw_safe_pixel(t_img_info *img_info, int x, int y, int color)
{
	int	color_byte;
	int	pixel;

	if (x >= 0 && x < img_info->width && y >= 0 && y < img_info->height)
	{
		color_byte = img_info->bpp / 8;
		pixel = (y * img_info->size_line) / color_byte + x;
		*(img_info->buf + pixel) = color;
	}
}
