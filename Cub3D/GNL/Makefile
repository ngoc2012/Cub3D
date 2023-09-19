# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minh-ngu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 10:56:09 by minh-ngu          #+#    #+#              #
#    Updated: 2023/09/04 07:10:40 by ngoc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBS = get_next_line.c get_next_line_utils.c
BONS = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS = ${LIBS:.c=.o}
BONO = ${BONS:.c=.o}
LIBN = libgnl.a 
CC = cc
CFLAGS = -Wall -Wextra -Werror
all: $(LIBN)
.c.o:
	$(CC) $(CFLAGS) -c -g $< -o ${<:.c=.o} -I.
bonus: $(BONO)
	ar rc $(LIBN) $(BONO)
$(LIBN): $(OBJS)
	ar rc $(LIBN) $(OBJS)
clean:
	rm -f $(OBJS)
	rm -f $(BONO)
fclean: clean
	rm -f $(LIBN)
re: fclean all
.PHONY:	all clean fclean re
