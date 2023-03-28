# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/04 12:34:12 by emandret          #+#    #+#              #
#    Updated: 2017/09/07 03:24:41 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR = src
SRC = builtins.c cd.c echo.c env.c exit.c gnl.c main.c setenv.c utils.c \
unsetenv.c

OBJDIR = obj
OBJ = $(SRC:.c=.o)

LIBDIR = libft
LIB = ftprintf

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(LIBDIR)/lib$(LIB).a $(OBJDIR) $(NAME)

$(LIBDIR)/lib$(LIB).a:
	@make -C $(LIBDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@$(CC) $(CFLAGS) $(addprefix $(OBJDIR)/, $(OBJ)) -o $(NAME) -L $(LIBDIR) -l $(LIB)
	@tput setaf 77 ; echo [DONE]

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo compiled $<

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBDIR)

re: fclean all

.PHONY: re fclean clean all
