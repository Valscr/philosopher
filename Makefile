# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 17:29:07 by valentin          #+#    #+#              #
#    Updated: 2022/12/19 02:27:20 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

C_FILES = philo.c init.c thread.c utils.c utils2.c

SRC_DIR = ./src/

DIR_OBJ = objs/

INCS	= -I ./include/

OBJS = ${C_FILES:%.c=$(DIR_OBJ)%.o}

CFLAGS += -pthread -Wall -Wextra -Werror

CC		= cc
RM		= rm -f

$(NAME): ${OBJS}
		@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
		@echo " [ $(COLOUR_GREEN)OK$(COLOUR_END) ] ./philo"

$(DIR_OBJ)%.o : $(SRC_DIR)%.c
		@mkdir -p $(DIR_OBJ)
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

all: ${NAME}

clean:
		@${RM} -rf ${DIR_OBJ}

fclean:	clean
		@${RM} ${NAME}
		@echo " [ OK ] philosopher is clean"

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c include/*.h 

.PHONY:         all clean fclean bonus re
