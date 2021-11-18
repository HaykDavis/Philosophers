# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psoares <psoares@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/18 02:12:46 by psoares           #+#    #+#              #
#    Updated: 2021/11/18 03:00:11 by psoares          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MY_PHILO	= philo

MY_PHILO_SRCS = philo.c \
			ft_utils.c \
			ft_inits.c \

HEADER		= philo.h

CC = gcc
RM = rm -f
FLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj/
OBJ_L = $(patsubst %.c, %.o, $(MY_PHILO_SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_L))

all: $(MY_PHILO)

$(MY_PHILO) : $(MY_PHILO_SRCS) $(HEADER)
	@$(CC) $(FLAGS) $(MY_PHILO_SRCS) -o $(MY_PHILO)
	@printf "Philo was build ✅\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $(MY_PHILO_SRCSLUDES)

clean:
		@$(RM) $(OBJ_DIR)
		@printf "ALL is in trash 🗑\n"

fclean: clean
		@$(RM) $(MY_PHILO)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re bonus rebonus