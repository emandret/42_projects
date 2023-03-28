# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/25 17:08:17 by emandret          #+#    #+#              #
#    Updated: 2019/01/22 21:32:54 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN       =  scop

SRCEXT    =  c
SRCDIR    =  src
OBJDIR    =  obj
BINDIR    =  bin

SRCS      := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS   := $(shell find . -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS      := $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))

INCLUDES  =  -I inc -I ~/.brew/include
CFLAGS    =  -fsanitize=address -pedantic -Wall -Wsign-compare -Wwrite-strings -Wtype-limits -Wextra -Werror -DGL_SILENCE_DEPRECATION -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED $(INCLUDES)
LDFLAGS   =  -fsanitize=address -lglfw -framework OpenGL
# CFLAGS    =  -pedantic $(INCLUDES)
# LDFLAGS   =  -pedantic -L ~/.brew/lib -lglfw -framework OpenGL

all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): mktree $(OBJS)
	@mkdir -p $$(dirname $@)
	@echo "Linking $@..."
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.$(SRCEXT)
	@echo "Generating dependencies for $<..."
	@$(CC) -MM -MF $(subst .o,.d,$@) -MP -MT $@ $(CFLAGS) $<
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

mktree:
	@for dir in $(SRCDIRS); do mkdir -p $(OBJDIR)/$$dir; done

clean:
	@$(RM) -rf $(OBJDIR)

fclean: clean
	@$(RM) -rf $(BINDIR)

re: fclean all

.PHONY: all mktree clean fclean re
