# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 14:36:59 by llepiney          #+#    #+#              #
#    Updated: 2022/07/28 16:28:43 by llepiney         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	ft_ulong_atoi.c main.c \
		philo_tools.c set_tools.c manage_tools.c check_args.c ft_atoi.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY : clean fclean re all