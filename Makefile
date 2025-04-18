# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 14:12:45 by enkwak            #+#    #+#              #
#    Updated: 2025/04/18 10:23:42 by enkwak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3
INCLUDES = -I./ -I./gnl -I./libft -I./minilibx -I./printf

SRCS = main.c \
	   parse.c parse_identifier.c parse_map.c validate_map.c utils.c player_rotate.c minimap.c \
	   event.c errors.c colors.c player.c player_move.c render_frame.c raycast.c init_textures.c \
	   

GNL_SRCS = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c

PRINTF_SRCS = \
	./printf/ft_printf.c \
	./printf/ft_putchar_pf.c \
	./printf/ft_putstr_pf.c \
	./printf/ft_putnbr_pf.c \
	./printf/ft_putuint_pf.c \
	./printf/ft_puthex_pf.c \
	./printf/ft_putptr_pf.c \
	./printf/ft_aux_pf.c

OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lX11 -lXext -lGL -lm -lpthread

all: $(LIBFT_A) $(NAME)

$(NAME): $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) $(LIBFT_A) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
