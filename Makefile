# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 14:47:10 by athonda           #+#    #+#              #
#    Updated: 2024/12/28 20:22:29 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
SRC_F	=	philosopher.c \
			util.c \
			init.c \
			constraint.c \
			friction.c \
			observation.c \
			time.c \
			monitoring.c
SRC = $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR = obj
OBJ =	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_F))

INC_DIR = inc
DEP = inc/philosopher.h

IFLAGS = -Iinc
CFLAGS = -g -Wall -Werror -Wextra

BONUS = philo_bonus

SRC_BONUS_DIR = bonus
SRC_BONUS_F = philo_bonus.c \

OBJ_B =	$(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_BONUS_F))

DEP_BONUS = inc/philosopher_bonus.h

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP)
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BONUS) : $(OBJ_B)
	cc $(CFLAGS) $(OBJ_B) -o $(BONUS)

$(OBJ_DIR)/%_bonus.o: $(SRC_BONUS_DIR)/%_bonus.c $(DEP_BONUS)
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) $(IFLAGS) -c $< -o $@

.PHONY: all clean fclean re

all: $(NAME)

bonus: $(BONUS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)
	rm $(BONUS)

re: fclean all
