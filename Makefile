# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 17:29:07 by valentin          #+#    #+#              #
#    Updated: 2022/12/17 17:34:11 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

C_FILES = philo.c

SRC_DIR = ./src/

DIR_OBJ = objs/

INCS	= -I ./include/

OBJS = ${C_FILES:%.c=$(DIR_OBJ)%.o}

CFLAGS += -pthread -Wall -Wextra -Werror

LIBSFLAGS	=  libft/libft.a

CC		= cc
RM		= rm -f

$(NAME): ${OBJS} maker
		@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBSFLAGS)
		@echo " [ $(COLOUR_GREEN)OK$(COLOUR_END) ] ./philo"

$(DIR_OBJ)%.o : $(SRC_DIR)%.c
		@mkdir -p $(DIR_OBJ)
		@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

all: ${NAME}

maker:
		@make -s -C libft
		@echo "[ OK ] libft"

clean:
		@${RM} -rf ${DIR_OBJ}
		@make fclean -s -C libft

fclean:	clean
		@${RM} ${NAME}
		@echo " [ OK ] philosopher is clean"

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c $(BONUS_DIR)*.c include/*.h 

.PHONY:         all clean fclean bonus re
