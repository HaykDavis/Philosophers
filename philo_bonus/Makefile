# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psoares <psoares@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 02:12:46 by psoares           #+#    #+#              #
#    Updated: 2021/11/28 14:23:43 by psoares          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MY_PHILO	= philo_bonus

MY_PHILO_SRCS = philo_bonus.c \
			ft_utils_bonus.c \
			ft_inits_bonus.c \
			philo_moves_bonus.c
			
SRC_DIR = src_bonus/
SRC = $(addprefix $(SRC_DIR), $(MY_PHILO_SRCS))

HEADER		= philo_bonus.h

CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror


OBJ_DIR = obj_bonus/
OBJ_L = $(patsubst %.c, %.o, $(MY_PHILO_SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_L))

all: $(MY_PHILO)

$(MY_PHILO) : $(OBJ) $(HEADER)
	@$(CC) $(FLAGS) $(OBJ) -o $(MY_PHILO)
	@printf "Philo_bonus was build ✅\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@

clean:
		@rm -rf $(OBJ_DIR)
		@printf "ALL is in trash 🗑\n"

fclean: clean
		@$(RM) $(MY_PHILO)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus rebonus