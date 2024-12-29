# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 14:47:10 by athonda           #+#    #+#              #
#    Updated: 2024/12/29 17:13:25 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC_DIR = src
SRC_F	=	philo_bonus.c
SRC = $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR = obj
OBJ =	$(patsubst %.c,%.o,$(SRC_F))

INC_DIR = inc
DEP = inc/philosopher_bonus.h

IFLAGS = -Iinc
CFLAGS = -g -Wall -Werror -Wextra

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(DEP)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all
