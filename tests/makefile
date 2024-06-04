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

INC=../parser.h
SRC=../parser.c test_parser.c
OBJS = test_parser.o ../parser.o
all: test_parser helper

%.o: %.c ${INC}
	$(CC) $(CFLAGS) -o $@ -c $<


test_parser:${OBJS} 
	${CC} $(CFLAGS) $^ -o $@

helper:helper.c
	$(CC) $(CFLAGS) $^ -o $@

clean: 
	rm -f *.o test_parser *.gch
