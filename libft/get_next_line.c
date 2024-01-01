/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:50:31 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 10:58:19 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_goto_next(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!str)
		return (free(str), NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	line = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (line == NULL)
		return (free(str), free(line), NULL);
	i++;
	j = 0;
	while (str[i])
		line[j++] = str[i++];
	line[j + 1] = 0;
	return (free(str), line);
}

char	*ft_first_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i])
	{
		line[i] = str[i];
		if (line[i] == '\n')
		{
			i++;
			line[i] = '\0';
			break ;
		}
		i++;
	}
	return (line);
}

char	*ft_read_file(int fd, char *str)
{
	int		byte_read;
	char	*tmp;

	if (!str)
		str = ft_calloc(1, 1);
	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, tmp, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(tmp), NULL);
		tmp[byte_read] = '\0';
		str = ft_strjoin(str, tmp);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	return (free(tmp), str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd >= 0 && read(fd, 0, 0) >= 0 && BUFFER_SIZE > 0)
	{
		str = ft_read_file(fd, str);
		if (!str)
			return (NULL);
		line = ft_first_line(str);
		str = ft_goto_next(str);
		return (line);
	}
	else
		return (free(str), str = NULL, NULL);
}
