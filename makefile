# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 16:34:38 by nbelouar42        #+#    #+#              #
#    Updated: 2024/06/02 16:35:17 by nbelouar42       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
CFLAGS =  -Wextra -Wall -Werror -g

INC=mini_shell.h
SRC=mini_shell.c
OBJS = mini_shell.o
all: mini

%.o: %.c ${INC}
	$(CC) $(CFLAGS) -o $@ -c $<
	
mini:${OBJS} 
	${CC} $(CFLAGS) $^ -o $@

clean: 
	rm -f *.o mini *.gch
