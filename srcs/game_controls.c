/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:56:24 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/24 18:40:50 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	try_move(t_cub *cub, int key)
{
	if (check_wall_collision(cub, key))
		return ;
	else if (key == 1)
	{
		cub->player_pos.x -= cub->player_pos.dirx * MOVESTEP;
		cub->player_pos.y -= cub->player_pos.diry * MOVESTEP;
	}
	else if (key == 13)
	{
		cub->player_pos.x += cub->player_pos.dirx * MOVESTEP;
		cub->player_pos.y += cub->player_pos.diry * MOVESTEP;
	}
	else if (key == 0)
	{
		cub->player_pos.x += cub->player_pos.diry * MOVESTEP;
		cub->player_pos.y -= cub->player_pos.dirx * MOVESTEP;
	}
	else if (key == 2)
	{
		cub->player_pos.x -= cub->player_pos.diry * MOVESTEP;
		cub->player_pos.y += cub->player_pos.dirx * MOVESTEP;
	}
	if (key == 124 || key == 123)
		adjust_player_rotation(cub, key, THREE_DEG);
	return ;
}

int	process_moves(t_cub *cub, int key)
{
	if (key == 13)
		try_move(cub, 13);
	if (key == 0)
		try_move(cub, 0);
	if (key == 1)
		try_move(cub, 1);
	if (key == 2)
		try_move(cub, 2);
	if (key == 124)
		try_move(cub, 124);
	if (key == 123)
		try_move(cub, 123);
	start_game(cub);
	return (0);
}

int	move(int key, t_cub *cub)
{
	if (key == 53)
		exit_hook(cub);
	process_moves(cub, key);
	return (1);
}

int	end_key_motion(int key, t_cub *cub)
{
	cub->key_state[key] = 0;
	return (0);
}
