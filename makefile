# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:34:38 by nbelouar42        #+#    #+#              #
#    Updated: 2024/06/03 14:19:11 by nbelouar42       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc 
CFLAGS =  -Wextra -Wall -Werror 

INC=mini_shell.h
SRC=parcing.c
OBJS = parcing.o
all:mini

%.o: %.c ${INC}
	$(CC) $(CFLAGS) -o $@ -c $<
	

mini:${OBJS} 
	${CC} $(CFLAGS) $^ -o $@

clean: 
	rm -f *.o mini *.gch

fclean: clean
	rm -f mini

re: fclean all
