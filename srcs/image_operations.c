/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:54:02 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:53:46 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

void	init_img(t_graphic_info *graphic_info, t_cub *cub)
{
	t_img_info	img_info;

	graphic_info->img = mlx_new_image(cub->mlx, WIN_SIZE_W, WIN_SIZE_H);
	img_info.buf = (unsigned int *)mlx_get_data_addr(graphic_info->img,
			&img_info.bpp,
			&img_info.size_line,
			&img_info.endian);
	graphic_info->img_info = img_info;
}

void	setup_graphic(t_graphic_info *graphic_info, t_cub *cub)
{
	int	i;

	init_img(graphic_info, cub);
	i = -1;
	while (++i < 4)
	{
		graphic_info->texture[i] = NULL;
	}
	i = -1;
	while (++i < 2)
		graphic_info->color[i] = -1;
}

void	*create_image(void *mlx_ptr, char *xpmFile, t_cub *cub)
{
	char	*path;
	void	*img;
	int		width;
	int		height;

	path = xpmFile;
	img = mlx_xpm_file_to_image(mlx_ptr, path, &width, &height);
	if (!img)
	{
		printf("Error\n");
		close_and_free_resources(cub, "Error\n");
	}
	return (img);
}

void	load_images(t_cub *cub)
{
	t_img_info	img_info;
	int			i;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			cub->graphic_info.texture[i] = create_image(cub->mlx, \
				cub->fetched->paths_mtx[3], cub);
		else if (i == 1)
			cub->graphic_info.texture[i] = create_image(cub->mlx, \
				cub->fetched->paths_mtx[0], cub);
		else if (i == 2)
			cub->graphic_info.texture[i] = create_image(cub->mlx, \
				cub->fetched->paths_mtx[1], cub);
		else if (i == 3)
			cub->graphic_info.texture[i] = create_image(cub->mlx, \
				cub->fetched->paths_mtx[2], cub);
		img_info.buf = \
			(unsigned *)mlx_get_data_addr(cub->graphic_info.texture[i],
				&img_info.bpp, &img_info.size_line, &img_info.endian);
		cub->graphic_info.texture_info[i] = img_info;
		i++;
	}
	return ;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
