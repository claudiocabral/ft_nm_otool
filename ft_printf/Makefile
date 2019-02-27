include printf.mk

CC		:=	cc
CFLAGS	:=	-Wextra -Werror -Wall
CDEBUG	:=	-g

NAME := $(PRINTF)

ifeq ($(DEBUG), 1)
	CFLAGS	+=	$(CDEBUG)
endif

.PHONY: all clean fclean re

include printf_rules.mk

all: $(NAME) Makefile

Makefile: printf.mk printf_rules.mk

fclean: $(PRINTF_FCLEAN)

clean: $(PRINTF_CLEAN)

re:
	$(MAKE) $(PRINTF_FCLEAN)
	$(MAKE) $(NAME)
