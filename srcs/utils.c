/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 10:09:00 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:56:57 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/program.h"

int	build_rgb_values(t_cub **cub, t_node *temp, int *i)
{
	int		k;
	int		h;
	int		nvalue;
	char	c[4];

	while (temp && (*i)++ < 7)
	{
		k = -1;
		nvalue = 0;
		while (temp->box[++k] && nvalue < 3)
			if (!validate_rgb_format(temp->box)
				|| !skip_non_digit_characters(temp->box, &k, &nvalue)
				|| !build_rgb_value(temp->box, &k, &h, c)
				|| !fetch_rgb_value(cub, c, nvalue, *i))
				return (0);
		temp = temp->next;
	}
	return (1);
}

int	split_information(t_node *info, t_cub **cub)
{
	t_node	*temp;
	int		i;

	(*cub)->fetched->paths_mtx = malloc(sizeof(char *) * 5);
	(*cub)->fetched->paths_mtx[0] = ft_substr(info->box, 3,
			ft_strlen(info->box));
	(*cub)->fetched->paths_mtx[1] = ft_substr(info->next->box, 3,
			ft_strlen(info->box));
	(*cub)->fetched->paths_mtx[2] = ft_substr(info->next->next->box, 3,
			ft_strlen(info->box));
	(*cub)->fetched->paths_mtx[3] = ft_substr(info->next->next->next->box, 3,
			ft_strlen(info->box));
		(*cub)->fetched->paths_mtx[4] = NULL;
	temp = info;
	i = 0;
	while (temp && i++ < 4)
		temp = temp->next;
	if (build_rgb_values(cub, temp, &i))
		return (1);
	return (0);
}

char	**node_list_to_matrix(t_node **head)
{
	t_node	*temp;
	char	**matrix;
	int		len;
	int		i;

	len = (*head)->prev->id;
	matrix = malloc(sizeof(char *) * len + 1);
	temp = *head;
	i = 0;
	while (temp && len--)
	{
		matrix[i] = ft_strdup(temp->box);
		i++;
		temp = temp->next;
	}
	matrix[i] = NULL;
	return (matrix);
}

int	validate_map_file(char *map_path)
{
	const char	*extension;
	char		*temp;
	int			ext_len;

	extension = ".cub";
	temp = map_path + strlen(map_path) - 1;
	ext_len = strlen(extension);
	while (ext_len >= 0 && *temp != '.' && temp >= map_path)
	{
		temp--;
		ext_len--;
	}
	if (ext_len < 0 || strcmp(temp, extension) != 0)
		return (-1);
	return (open(map_path, O_RDONLY));
}
