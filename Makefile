# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/25 19:24:54 by ivbatist          #+#    #+#              #
#    Updated: 2023/10/25 19:24:59 by ivbatist         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT	= ./lib/libft.a
LIBFT_DIR = ./lib

MINILIBX = ./minilibx-linux/libmlx_Linux.a
MINILIBX_DIR = ./minilibx-linux

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -f

SRCSCUBED = ./src/cub3d.c ./src/dda.c ./src/exit.c ./src/hooks_control.c \
			./src/others.c ./src/raycaster.c ./src/textures.c ./src/utils_minilbx.c\
			./src/vd2d_operations.c ./src/parse_cub_file.c ./src/map_parse.c \
			./src/utils.c ./src/parse_elements.c

NAME = cub3D

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(NAME): $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCSCUBED) -o $(NAME) -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)
	$(RM) $(NAME)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re




