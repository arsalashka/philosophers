# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maearly <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/11 16:34:47 by maearly           #+#    #+#              #
#    Updated: 2021/06/11 16:34:51 by maearly          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIST =			main.c init_data.c threads.c printer.c action.c \
				utils/ft_error.c utils/ft_atoi.c utils/ft_itoa.c \
				utils/ft_strlen.c utils/get_time.c utils/ft_strdup.c

OBJ = $(patsubst %.c,%.o,$(LIST))

D_FILES = $(patsubst %.c,%.d,$(LIST))

OTPFLAGS = -O2

FLAGS = -Wall -Wextra -Werror

all :	$(NAME)

$(NAME) :	$(OBJ)
	gcc $(FLAGS) $(OPTFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	gcc $(FLAGS) $(OPTFLAGS) -c $< -o $@ -MD

include $(wildcard $(D_FILES))

clean :
	rm -f $(OBJ) $(D_FILES)

fclean : clean
	rm -f $(NAME) $(D_FILES)

re : fclean all

.PHONY : all clean fclean re