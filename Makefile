# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/10/09 21:47:11 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c map.c draw.c mini_map.c hook.c math.c texture.c sprites.c	render_box.c get_A.c get_B.c frames.c for_check.c for_hero_map.c
MSRC = $(addprefix srcs/, $(SRCS))
MOBJ = ${MSRC:.c=.o}
MANDA = cub3D
CC = cc
#FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall
LIBFT = libft/libft.a
LIBGNL = GNL/libgnl.a
LIBML = minilibx-linux/libft_Linux.a
INCL_MINILIBX = -I./minilibx-linux
OBJ_MINILIBX = -L./minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz
LIBS = libft GNL
all:	$(MANDA)
$(LIBFT):
	make -C libft
$(LIBGNL):
	make -C GNL
$(LIBML):
	make -C minilibx-linux
.c.o:
	$(CC) $(FLAGS) $(INCL_MINILIBX) -g -c $< -o ${<:.c=.o} $(addprefix -I./, $(LIBS) includes)
$(MANDA):	$(MOBJ) $(LIBFT) $(LIBGNL) $(LIBML) 
	$(CC) $(FLAGS) $(MOBJ) $(OBJ_MINILIBX) -L./libft -lft -L./GNL -lgnl -o $(MANDA)
bonus:	$(MANDA)
norm:
	norminette $(LIBS) srcs includes
gits:
	git add Makefile
	git add $(addsuffix /Makefile, $(LIBS))
	git add $(addsuffix /*.c, $(LIBS) srcs)
	git add $(addsuffix /*.h, $(LIBS) includes)
	git commit -m "all"
	git push
sdgits:
	git add -A
	git commit -m "all"
	git push
clean:
	make clean -C libft
	make clean -C GNL
	make clean -C minilibx-linux
	rm -f $(MOBJ)
fclean: clean
	make fclean -C libft	
	make fclean -C GNL	
	make clean -C minilibx-linux
	rm -f $(MANDA)
re: fclean all
.PHONY: all clean fclean re
