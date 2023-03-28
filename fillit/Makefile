# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/11 00:16:40 by emandret          #+#    #+#              #
#    Updated: 2016/12/11 00:39:49 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fillit

LIB=./libft/libft.a

SRC=block_class.c \
	map_class.c \
	open_file.c \
	parser.c \
	solver.c \
	storage_class.c \
	tetri_class.c \
	main.c

CC=clang

CFLAGS=-Wall -Wextra -Werror

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB)
	$(CC) $(CFLAGS) -c $(addprefix ./srcs/, $(SRC)) -I . -I ./libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L ./libft -l ft

$(LIB):
	make re -C ./libft

clean:
	rm -rf $(OBJ)
	make clean -C ./libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
