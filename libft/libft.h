/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:45:36 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 14:47:17 by ygolshan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>

long long	a_(char *str, int len_base);
int			ft_isdigit(char c);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_isspace(int c);
char		*ft_strtrim(const char *s1, const char *set);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *b, size_t n);
char		*ft_strstr(char *str, char *to_find);
void		*ft_memset(void *b, int c, size_t len);
char		*get_next_line(int fd);

#endif
