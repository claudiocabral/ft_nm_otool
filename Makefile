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
LIB := binary_utils
NAME_LIB := lib$(LIB).a
ifeq (CC,)
CC		:= cc
endif

CFLAGS	:=	$(CFLAGS) -Wextra -Werror -Wall -march=native -Wshadow
CDEBUG	:=	-g
PRINTF_PATH := 	ft_printf


DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.dep && touch $@

include $(PRINTF_PATH)/printf.mk

OBJS_NM		=	objs/nm/main.o
OBJS_OTOOL	=	objs/otool/main.o
OBJS_LIB	=	objs/binary_library/map_file.o\
				objs/binary_library/mach_o.o\
				objs/binary_library/fat.o\
				objs/binary_library/static.o\
				objs/binary_library/apply.o\
				objs/binary_library/get_type.o\
				objs/binary_library/segments.o\
				objs/binary_library/section.o\
				objs/binary_library/hexdump.o\
				objs/binary_library/ft_put.o\
				objs/binary_library/ft_strncmp.o\
				objs/binary_library/print.o\
				objs/binary_library/sort.o\
				objs/binary_library/utils.o\
				objs/binary_library/choose_type.o

INC	=	-Iincludes \
		-I$(PRINTF_INCLUDES)

ifeq ($(ASAN), 1)
	DEBUG := 1
	CDEBUG += -fsanitize=address
endif

ifeq ($(DEBUG), 1)
	CFLAGS	+=	$(CDEBUG)
endif

OS = $(shell uname -s)

.PHONY: all clean fclean re

all: $(NAME) $(NAME_OTOOL) $(NAME_LIB)

include $(PRINTF_PATH)/printf_rules.mk

$(NAME): $(OBJS_NM) $(NAME_LIB) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_NM) $(INC)\
		-L. -l$(LIB) -L$(PRINTF_PATH) -lftprintf\
		-o $@

$(NAME_OTOOL): $(OBJS_OTOOL) $(NAME_LIB) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_OTOOL) $(INC)\
		-L. -l$(LIB) -L$(PRINTF_PATH) -lftprintf\
		-o $@

$(NAME_LIB): $(OBJS_LIB) $(PRINTF)
	ar rcs $@ $^

objs/%.o: srcs/%.c $(DEPDIR)/%.dep Makefile
	$(eval DIR := $(dir $@))
	$(eval CURRENT_DEPDIR := $(DIR:objs/%=$(DEPDIR)/%))
	@[[ -d $(DIR) ]] || mkdir -p $(DIR)
	@[[ -d $(CURRENT_DEPDIR) ]] || mkdir -p $(CURRENT_DEPDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC) $(DEPFLAGS)
	$(POSTCOMPILE)

$(DEPDIR)/%.dep: ;
.PRECIOUS: $(DEPDIR)/%.dep

include $(wildcard $(OBJS_NM:objs/%.o=$(DEPDIR)/%.dep))
include $(wildcard $(OBJS_LIB:objs/%.o=$(DEPDIR)/%.dep))
include $(wildcard $(OBJS_OTOOL:objs/%.o=$(DEPDIR)/%.dep))

fclean: clean
	$(MAKE) $(PRINTF_FCLEAN)
ifeq ($(shell [ -e $(NAME) ] && echo 1 || echo 0),1)
	rm -rf $(NAME)
endif
ifeq ($(shell [ -e $(NAME_LIB) ] && echo 1 || echo 0),1)
	rm -rf $(NAME_LIB)
endif

clean:
	$(MAKE) $(PRINTF_CLEAN)
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
