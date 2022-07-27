# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/27 14:36:59 by llepiney          #+#    #+#              #
#    Updated: 2022/07/27 15:35:32 by llepiney         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	ft_ulong_atoi.c main.c \
		philo_tools.c set_tools.c manage_tools.c \

# SRC_BONUS = 

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

bonus: $(OBJ_BONUS) philo.h
	$(CC) $(CFLAGS) -o philo_bonus $(OBJ_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS) 

fclean: clean
	rm -f $(NAME)
	rm -f philo_bonus

re: fclean all


.PHONY : clean fclean bonus re all