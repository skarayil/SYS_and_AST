# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/29 18:15:50 by skarayil          #+#    #+#              #
#    Updated: 2026/10/29 18:15:52 by skarayil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = vbc
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c tree.c error.c parse.c eval.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re