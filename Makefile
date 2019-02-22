# **************************************************************************** #
#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 19:57:39 by claudioca         #+#    #+#              #
#    Updated: 2018/06/09 16:58:09 by ctrouill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	ft_nm
NAME_OTOOL :=	ft_otool
NAME_LIB := libbinary_utils.a
ifeq (CC,)
CC		:= cc
endif

CFLAGS	:=	$(CFLAGS) -Wextra -Werror -Wall -march=native -Wshadow
CDEBUG	:=	-g


DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.dep && touch $@

OBJS_NM		=	objs/nm/main.o
OBJS_OTOOLS	=	objs/binary_library/map_file.o
OBJS_LIB	=	objs/binary_library/map_file.o\
			objs/binary_library/parse64.o\
			objs/binary_library/parse32.o\
			objs/binary_library/choose_type.o

INC	=	-Iincludes

ifeq ($(ASAN), 1)
	DEBUG := 1
	CDEBUG += -fsanitize=address
endif

ifeq ($(DEBUG), 1)
	CFLAGS	+=	$(CDEBUG)
endif

OS = $(shell uname -s)

.PHONY: all clean fclean re

all: $(NAME) $(NAME_LIB)

$(NAME_LIB): $(OBJS_LIB)
	ar rcs $@ $^

$(NAME): $(OBJS_NM) $(NAME_LIB)
	$(CC) $(CFLAGS) $(OBJS_NM) $(INC) -o $@ $(NAME_LIB)

objs/%.o: srcs/%.c $(DEPDIR)/%.dep Makefile
	$(eval DIR := $(dir $@))
	$(eval CURRENT_DEPDIR := $(DIR:objs/%=$(DEPDIR)/%))
	@[[ -d $(DIR) ]] || mkdir -p $(DIR)
	@[[ -d $(CURRENT_DEPDIR) ]] || mkdir -p $(CURRENT_DEPDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC) $(DEPFLAGS)
	$(POSTCOMPILE)

$(DEPDIR)/%.dep: ;
.PRECIOUS: $(DEPDIR)/%.dep

include $(wildcard $(OBJS:objs/%.o=$(DEPDIR)/%.dep))

fclean: clean
ifeq ($(shell [ -e $(NAME) ] && echo 1 || echo 0),1)
	rm -rf $(NAME)
endif
ifeq ($(shell [ -e $(NAME_LIB) ] && echo 1 || echo 0),1)
	rm -rf $(NAME_LIB)
endif

clean:
ifeq ($(shell [ -e $(DEPDIR) ] && echo 1 || echo 0),1)
	rm -rf $(DEPDIR)
endif
ifeq ($(shell [ -e $(NAME).dSYM ] && echo 1 || echo 0),1)
	rm -rf $(NAME).dSYM
endif
ifeq ($(shell [ -e objs ] && echo 1 || echo 0),1)
	rm -rf objs
endif

re:
	$(MAKE) fclean
	$(MAKE) all
