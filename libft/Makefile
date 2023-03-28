# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/29 08:30:05 by emandret          #+#    #+#              #
#    Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

INCDIR	=	incs
SRCDIR	=	srcs

SRC		=	ft_atoi.c \
			ft_bzero.c \
			ft_intswap.c \
			ft_is_whitespace.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isblank.c \
			ft_isdigit.c \
			ft_islower.c \
			ft_isprint.c \
			ft_isupper.c \
			ft_itoa.c \
			ft_itoa_base.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_max.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_pow.c \
			ft_ptrswap.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putwchar.c \
			ft_putwchar_fd.c \
			ft_putwendl.c \
			ft_putwendl_fd.c \
			ft_putwstr.c \
			ft_putwstr_fd.c \
			ft_realloc.c \
			ft_split_whitespaces.c \
			ft_sqrt.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcount.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strrep.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtolower.c \
			ft_strtoupper.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_utf8_encode.c \
			ft_wcsize.c \
			ft_wctomb.c \

OBJDIR	=	objs

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-I$(INCDIR) -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJDIR) $(addprefix $(OBJDIR)/, $(OBJ))
	@ar rc $(NAME) $(addprefix $(OBJDIR)/, $(OBJ))
	@ranlib $(NAME)
	@tput setaf 77; echo finished $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo compiled $<

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
