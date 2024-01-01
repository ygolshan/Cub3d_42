/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initializer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:52:45 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:52:43 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	init_fetch(t_cub *cub)
{
	cub->fetched = malloc(sizeof(t_fetch));
	cub->fetched->colors = NULL;
	cub->fetched->map = NULL;
	cub->fetched->paths_mtx = NULL;
	cub->fetched->colors_str = NULL;
	cub->fetched->p_t = NULL;
	cub->fetched->len = 0;
	cub->fetched->checks = NULL;
	cub->player_existence = 0;
	cub->fetched->map_mtx = NULL;
	add_tail(&cub->fetched->checks, new_("WE", 1));
	add_tail(&cub->fetched->checks, new_("NO", 2));
	add_tail(&cub->fetched->checks, new_("SO", 3));
	add_tail(&cub->fetched->checks, new_("EA", 4));
	add_tail(&cub->fetched->checks, new_("F ", 5));
	add_tail(&cub->fetched->checks, new_("C ", 6));
	cub->player_pos.x = 0.;
	cub->player_pos.y = 0.;
	cub->player_pos.wd = 0.;
}

void	init_statics(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		cub->wall_imgs_addrs[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		cub->wall_imgs[i] = NULL;
		i++;
	}
	i = 0;
	while (i < KEY_COUNT)
		cub->key_state[i++] = 0;
	cub->mat_tmp = NULL;
	cub->str_tmp = NULL;
	cub->data->img = mlx_new_image(cub->mlx, WIN_SIZE_W, WIN_SIZE_H);
	cub->data->addr = mlx_get_data_addr(cub->data->img, \
		&cub->data->bits_per_pixel, &cub->data->line_length, \
			&cub->data->endian);
	cub->player_pos.angle = 0.f;
}

void	adjust_player_rotation(t_cub *cub, int key, double angle)
{
	double	old_dirx;
	double	old_diry;
	double	old_planex;
	double	old_planey;

	if (key == 123)
		angle *= -1;
	old_dirx = cub->player_pos.dirx;
	old_diry = cub->player_pos.diry;
	old_planex = cub->player_pos.plane.x;
	old_planey = cub->player_pos.plane.y;
	cub->player_pos.dirx = old_dirx * cos(angle) - old_diry * sin(angle);
	cub->player_pos.diry = old_dirx * sin(angle) + old_diry * cos(angle);
	cub->player_pos.plane.x = old_planex * cos(angle) - old_planey * sin(angle);
	cub->player_pos.plane.y = old_planex * sin(angle) + old_planey * cos(angle);
}

void	adjust_player_position(t_cub *tmp, int key)
{
	if (key == 1)
	{
		tmp->player_pos.x -= tmp->player_pos.dirx * MOVESTEP;
		tmp->player_pos.y -= tmp->player_pos.diry * MOVESTEP;
	}
	else if (key == 13)
	{
		tmp->player_pos.x += tmp->player_pos.dirx * MOVESTEP;
		tmp->player_pos.y += tmp->player_pos.diry * MOVESTEP;
	}
	else if (key == 0)
	{
		tmp->player_pos.y -= tmp->player_pos.dirx * MOVESTEP;
		tmp->player_pos.x += tmp->player_pos.diry * MOVESTEP;
	}
	else if (key == 2)
	{
		tmp->player_pos.y += tmp->player_pos.dirx * MOVESTEP;
		tmp->player_pos.x -= tmp->player_pos.diry * MOVESTEP;
	}
}

int	game_init(t_cub *cub)
{
	t_data	*d;

	d = NULL;
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		printf("Error\n");
		return (0);
	}
	cub->win = mlx_new_window(cub->mlx, WIN_SIZE_W, WIN_SIZE_H, "cub3d");
	if (!cub->win)
	{
		printf("Error\n");
		return (0);
	}
	d = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!d)
	{
		printf("Error\n");
		return (0);
	}
	cub->data = d;
	init_fetch(cub);
	init_statics(cub);
	return (1);
}
