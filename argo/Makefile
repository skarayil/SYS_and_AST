# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/29 18:18:39 by skarayil          #+#    #+#              #
#    Updated: 2026/10/29 18:18:40 by skarayil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = argo
CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c99
SRC = main.c argo.c parse.c error.c memory.c serialize.c
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