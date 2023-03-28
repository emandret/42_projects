# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/14 02:41:29 by emandret          #+#    #+#              #
#    Updated: 2019/01/16 03:50:43 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ssl
LIBS		=	libft/libft.a

SRCDIR		=	src
OBJDIR		=	obj

INCLUDES	=	-I inc -I libft/inc
CFLAGS		=	-fsanitize=address -Wall -Wall -Werror
LDFLAGS		=	-fsanitize=address -L libft -l ft -Wall -Wall -Werror

SRCS		=	main.c														\
				handler_md5.c												\
				algo_md5.c													\
				tools_md5.c													\
				handler_sha256.c											\
				algo_sha256.c												\
				tools_sha256.c												\
				tools.c

# ================================ Do not touch ================================
SRCS		:=	$(addprefix $(SRCDIR)/, $(SRCS))
SRCDIRS		:=	$(sort $(dir $(SRCS)))
OBJS		:=	$(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))
# ==============================================================================

all: mktree $(NAME)

$(NAME): $(LIBS) $(OBJS)
	@mkdir -p $$(dirname $@)
	@echo "Linking $@..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(LIBS):
	@make -C $(dir $(LIBS))

$(OBJDIR)/%.o: %.c
	@echo "Generating dependencies for $<..."
	@$(CC) -MM -MF $(subst .o,.d,$@) -MP -MT $@ $(CFLAGS) $(INCLUDES) $<
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

mktree:
	@for dir in $(SRCDIRS); do mkdir -p $(OBJDIR)/$$dir; done

clean:
	@$(RM) -rf $(OBJDIR)

fclean: clean
	@$(RM) -rf $(NAME)
	@make fclean -C $(dir $(LIBS))

re: fclean all

.PHONY: all mktree clean fclean re
