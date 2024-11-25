# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 14:47:10 by athonda           #+#    #+#              #
#    Updated: 2024/11/25 17:17:25 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopfer

SRC_DIR = src
SRC_F	=	philosopher.c \
			error.c \
			util.c
SRC = $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR = obj
OBJ =	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_F))

INC_DIR = inc
DEP = inc/philosopher.h

INC_FLAGS = -Iinc
CFLAGS = -g -Wall -Wextra - Werror


$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(DEP)
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY all clean fclean re

all	: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: fclean all
