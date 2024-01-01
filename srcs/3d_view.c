/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:52:06 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 15:23:48 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	render_vertical_line(t_player *sp, t_player *ep, t_cub *cub)
{
	double		m;
	double		k;
	t_player	point;
	int			size;
	int			i;

	m = (sp->y - ep->y) / (sp->x - ep->x);
	k = sp->y - m * (sp->x);
	size = fabs(sp->y - ep->y);
	if (sp->y < ep->y)
		point.y = sp->y;
	else
		point.y = ep->y;
	i = 0;
	while (i <= size)
	{
		if (sp->x != ep->x)
			point.x = floor(((point.y + i) - k) / m + 0.5);
		else
			point.x = sp->x;
		my_mlx_pixel_put(cub->data, point.x, point.y + i, 0x0000ff);
		i++;
	}
}

void	render_horizontal_line(t_player *sp, t_player *ep, t_cub *cub)
{
	double		m;
	double		k;
	t_player	point;
	int			size;
	int			i;

	m = (sp->y - ep->y) / (sp->x - ep->x);
	k = sp->y - m * (sp->x);
	size = fabs(sp->x - ep->x);
	if (sp->x < ep->x)
		point.x = sp->x;
	else
		point.x = ep->x;
	i = 0;
	while (i <= size)
	{
		point.y = floor(m * (point.x + i) + k + 0.5);
		my_mlx_pixel_put(cub->data, point.x + i, point.y, 0x0000ff);
		i++;
	}
}

void	render_line(t_player *sp, t_player *ep, t_cub *cub)
{
	if (fabs(sp->x - ep->x) < 1)
	{
		render_vertical_line(sp, ep, cub);
	}
	else
	{
		render_horizontal_line(sp, ep, cub);
	}
}

void	render_ray(t_cub *cub, t_ray *ray)
{
	t_player	sp;
	t_player	ep;
	int			b_size;

	if ((int)ft_strlen(cub->map[0]) > count_rows_in_matrix(cub->map))
		b_size = MINI_WIN_SIZE / ft_strlen(cub->map[0]);
	else
		b_size = MINI_WIN_SIZE / count_rows_in_matrix(cub->map);
	sp.x = b_size * cub->player_pos.x;
	sp.y = b_size * cub->player_pos.y;
	if (ray->side == 0)
	{
		ep.y = b_size * (cub->player_pos.y + \
			ray->perp_wall_dist * ray->ray_dir.y);
		ep.x = b_size * (cub->player_pos.x + \
			ray->perp_wall_dist * ray->ray_dir.x);
	}
	else
	{
		ep.y = b_size * (cub->player_pos.y + \
			ray->perp_wall_dist * ray->ray_dir.y);
		ep.x = b_size * (cub->player_pos.x + \
			ray->perp_wall_dist * ray->ray_dir.x);
	}
	render_line(&sp, &ep, cub);
}

void	draw_rays(t_cub *cub, float mapw, int b_size)
{
	int		x;
	double	camera_x;
	t_ray	ray;

	x = 0;
	while (x * 10 < (int)(mapw * b_size))
	{
		camera_x = 2 * (x * 10) / (double)(mapw * b_size) - 1;
		ray = calculate_raycast(cub, cub->map, camera_x);
		render_ray(cub, &ray);
		x++;
	}
}
