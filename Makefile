# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhodara <akhodara@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/22 09:35:56 by ygolshan          #+#    #+#              #
#    Updated: 2023/09/25 17:46:03 by akhodara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Wall
SRCS = 	./srcs/cleanup.c \
		./srcs/game_renderer.c \
		./srcs/game_renderer_functions.c \
		./srcs/3d_view.c \
		./srcs/game_initializer.c \
		./srcs/stack_operations.c \
		./srcs/image_operations.c \
		./srcs/main.c \
		./srcs/map_validation.c \
		./srcs/game_controls.c \
		./srcs/parser.c \
		./srcs/character_utils.c \
		./srcs/data_processing.c \
		./srcs/player_setup.c \
		./srcs/raycast.c \
		./srcs/validate_rgb_format.c \
		./srcs/utils.c \
		./srcs/utils1.c \
		./srcs/utils2.c 
	   
OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx
LIBFT_DIR = libft
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
LIBFT_FLAGS = -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -O3 -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS)

clean:
	-rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: fclean clean re all
