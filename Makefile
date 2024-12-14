# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 14:47:10 by athonda           #+#    #+#              #
#    Updated: 2024/12/14 20:39:30 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
SRC_F	=	philosopher.c \
			error.c \
			util.c \
			init.c \
			constraint.c \
			friction.c \
			time.c \
			monitoring.c
SRC = $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR = obj
OBJ =	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_F))
#OBJ = $(OBJ_F:%.o=$(OBJ_DIR)/%.o)

INC_DIR = inc
DEP = inc/philosopher.h

IFLAGS = -Iinc
CFLAGS = -g -Wall -Werror -Wextra

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP)
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all
