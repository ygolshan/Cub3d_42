# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygolshan <ygolshan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:46:25 by ygolshan          #+#    #+#              #
#    Updated: 2023/09/25 11:16:06 by ygolshan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.so

SOURCE = ft_atoi.c \
		 ft_bzero.c \
		 ft_calloc.c \
		 ft_isdigit.c \
		 ft_isspace.c \
		 ft_itoa.c \
		 ft_memset.c \
		 ft_split.c \
		 ft_strchr.c \
		 ft_strcmp.c \
		 ft_strdup.c \
		 ft_strjoin.c \
		 ft_strlen.c \
		 ft_strtrim.c \
		 ft_substr.c \
		 get_next_line.c

OBJECT = $(SOURCE:%.c=%.o)


all : $(NAME)

$(NAME) : $(OBJECT)
	ar -rcs $(NAME) $^


%.o : %.c
	cc -c -Wall -Wextra -Werror $^

clean :
	rm -f $(OBJECT)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: fclean clean re all