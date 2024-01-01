/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:02:49 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:55:19 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	validate_info_data(t_node **info, t_fetch *fetched)
{
	if (check_data_presence(*info, fetched) == 6)
		if (adjust_info_data(info, fetched))
			if (update_information(info, fetched))
				return (1);
	return (0);
}

void	append_info_data(t_node **info, char *temp, int *i, t_cub **cub)
{
	if (*i < 6)
		add_tail(info, new_(temp, ++(*i)));
	else
		add_tail(&(*cub)->fetched->map,
			new_(temp, ++(*i)));
}

int	validate_map_data(t_cub **cub, t_node **info)
{
	if (!(*cub)->fetched->map || !*info)
		return (0);
	relist_nodes(&(*cub)->fetched->map);
	if (check_wall_row((*cub)->fetched->map->box)
		&& check_wall_row((*cub)->fetched->map->prev->box))
		if (validate_map(cub))
			if (map_checks(cub, 0))
				if (standard_map(cub))
					return (1);
	return (0);
}

int	parse_and_build_info(int fd, t_node **info, t_cub **cub, int i)
{
	char	*line;
	char	*temp;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n"))
		{
			temp = ft_strtrim(line, " \t\n");
			append_info_data(info, temp, &i, cub);
			if ((*cub)->fetched->len < (int)ft_strlen(line))
				(*cub)->fetched->len = ft_strlen(line) - 1;
			free(temp);
		}
		else if (!ft_strcmp(line, "\n") && i > 6)
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (validate_map_data(cub, info))
		return (1);
	return (0);
}

int	parser(int fd, t_cub *cub)
{
	t_node	*info;

	info = NULL;
	if (fd > 0)
		if (parse_and_build_info(fd, &info, &cub, 0))
			if (validate_info_data(&info, cub->fetched))
				if (split_information(info, &cub))
					return (1);
	free_content(info);
	free_list(&info);
	return (0);
}
