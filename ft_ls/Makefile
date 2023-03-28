# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/07 11:43:53 by emandret          #+#    #+#              #
#    Updated: 2017/05/31 20:56:08 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

LIB=libft/libftprintf.a

SRC=dirs.c ft_ls.c node.c node_swap.c opts.c print.c sort.c data.c lst.c \
utils.c perms.c

OBJ=$(SRC:.c=.o)

CFLAGS=-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIB)
	@$(CC) $(CFLAGS) -c $(addprefix src/, $(SRC))
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L libft -l ftprintf

$(LIB):
	@make re -C libft

clean:
	@rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
