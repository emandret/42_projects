# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/19 12:39:07 by emandret          #+#    #+#              #
#    Updated: 2017/08/22 16:55:36 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isblanks.c ft_isdigit.c ft_islower.c ft_isprint.c ft_isupper.c \
ft_itoa.c ft_itoa_base.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_ltoa_base.c ft_memalloc.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_sqrt.c ft_strcat.c \
ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strjoin_free.c \
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
ft_strstr.c ft_strsub.c ft_strtolower.c ft_strtoupper.c ft_strtrim.c \
ft_tolower.c ft_toupper.c ft_ultoa_base.c ft_wcharlen.c ft_wstrlen.c \
ft_chrncpy.c ft_getenv.c ft_getpath.c ft_strfchr.c ft_tabdup.c ft_strrep.c \
ft_strcount.c ft_split_whitespaces.c ft_tabsize.c ft_tabswap.c ft_tabfree.c

PRINTF = ft_printf.c pf_buffer.c pf_handle.c pf_handle_chr.c pf_handle_hex.c \
pf_handle_num.c pf_handle_oct.c pf_handle_ptr.c pf_handle_str.c \
pf_handle_uni.c pf_handle_uns.c pf_helper.c pf_parse_conv.c pf_parse_flag.c \
pf_parse_modi.c pf_parse_numb.c pf_parser.c pf_unicod.c

OBJ = $(SRC:.c=.o) $(PRINTF:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -c $(addprefix src/libft/, $(SRC)) $(addprefix src/printf/, $(PRINTF))
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
