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


MINILIBX = ./minilibx-linux/libmlx_Linux.a
MINILIBX_DIR = ./minilibx-linux

CC	= cc -Wall -Wextra -Werror
RM	= rm -f

SRCSCUBED = 	./cub3d.c ./hook_utils.c ./map_update1.c ./render_utils.c ./utils.c ./moves.c ./raycaster.c

NAME = cub3d

all:	$(NAME)


$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(NAME): $(MINILIBX)
	$(CC) -g $(SRCSCUBED) $(MINILIBX) -lXext -lX11 -lm -o $(NAME)

clean:
	make clean -C $(MINILIBX_DIR)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.SILENT:
