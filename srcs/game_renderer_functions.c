/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:51:46 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 15:16:12 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	render_player(t_cub *cub)
{
	float	center_x;
	float	center_y;
	float	mapw;
	float	maph;
	int		b_size;

	mapw = ft_strlen(cub->map[0]);
	maph = count_rows_in_matrix(cub->map);
	if (mapw > maph)
		b_size = MINI_WIN_SIZE / mapw;
	else
		b_size = MINI_WIN_SIZE / maph;
	center_x = (cub->player_pos.x) * b_size;
	center_y = (cub->player_pos.y) * b_size;
	my_mlx_pixel_put(cub->data, (int)(center_x), (int)(center_y), 0x0cddddf);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->data->img, 0, 0);
}

void	draw_block(t_cub *cub, int i, int j, int color)
{
	float	k;
	float	m;
	int		b_size;
	float	mapw;
	float	maph;

	mapw = ft_strlen(cub->map[0]);
	maph = count_rows_in_matrix(cub->map);
	if (mapw > maph)
		b_size = MINI_WIN_SIZE / mapw;
	else
		b_size = MINI_WIN_SIZE / maph;
	m = 0;
	while (m < b_size)
	{
		k = 0;
		while (k < b_size)
		{
			my_mlx_pixel_put(cub->data, (int)((j * b_size) + m), \
				(int)((i * b_size) + k), color);
			k++;
		}
		m++;
	}
}

void	process_maprow(t_cub *cub, int i, float mapw)
{
	int	j;
	int	color;

	j = 0;
	while (j < mapw)
	{
		if (cub->map[i][j] == '1')
			color = 0x00FF00;
		else
			color = 0xFFFFFF;
		draw_block(cub, i, j, color);
		j++;
	}
}

void	render_block(t_cub *cub, float mapw, float maph)
{
	int	i;

	i = 0;
	while (i < maph)
	{
		process_maprow(cub, i, mapw);
		i++;
	}
}

int	render_minimap(t_cub *cub)
{
	float	mapw;
	float	maph;
	int		b_size;

	mapw = ft_strlen(cub->map[0]);
	maph = count_rows_in_matrix(cub->map);
	if (mapw > maph)
		b_size = MINI_WIN_SIZE / mapw;
	else
		b_size = MINI_WIN_SIZE / maph;
	render_block(cub, mapw, maph);
	draw_rays(cub, mapw, b_size);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->data->img, 0, 0);
	return (0);
}
