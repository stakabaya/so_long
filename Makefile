# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/03 02:04:56 by stakabay          #+#    #+#              #
#    Updated: 2021/11/25 09:15:18 by stakabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long
CC := gcc -g -fsanitize=address
CFLAGS := -Wall -Wextra -Werror
SRCNAME	=	main.c \
			get_map.c \
			read_mapfile.c \
			read_elements.c \
			image_opration.c \
			game_start.c \
			draw.c

OBJS := $(SRCNAME:.c=.o)
LIBFT := libft.a
LIBFT_DIR := ./libft/
LIBMLX := libmlx_Linux.a
LIBMLX_DIR := ./minilibx-linux/
GNL_DIR:= ./GNL/
GNL := get_next_line.a
RM := rm -f

all:$(NAME)

$(NAME):$(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(LIBMLX_DIR)
	$(MAKE) -C $(GNL_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT) $(LIBMLX_DIR)$(LIBMLX) $(GNL_DIR)$(GNL) -L. -lXext -lX11 -lm -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(LIBMLX_DIR)
	$(MAKE) clean -C $(GNL_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT) $(LIBMLX) $(GNL) 
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)

re:			fclean all

.PHONY:		clean fclean re all
