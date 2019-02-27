ifeq ($(PRINTF_PATH),)
	PRINTF_PATH := .
endif
PRINTF	:=	$(PRINTF_PATH)/libftprintf.a
PRINTF_FCLEAN := printf_fclean
PRINTF_CLEAN := printf_clean
PRINTF_INCLUDES	:=	$(PRINTF_PATH)/includes
PRINTF_OBJS_DIR :=	$(PRINTF_PATH)/objs
PRINTF_OBJS	:=	\
				$(PRINTF_OBJS_DIR)/ft_printf.o \
				$(PRINTF_OBJS_DIR)/get_function.o \
				$(PRINTF_OBJS_DIR)/get_printer.o \
				$(PRINTF_OBJS_DIR)/modifiers.o \
				$(PRINTF_OBJS_DIR)/utils.o \
				$(PRINTF_OBJS_DIR)/getters_0.o \
				$(PRINTF_OBJS_DIR)/getters_1.o \
				$(PRINTF_OBJS_DIR)/percent.o \
				$(PRINTF_OBJS_DIR)/conversion.o \
				$(PRINTF_OBJS_DIR)/wild_card.o \
				$(PRINTF_OBJS_DIR)/print_base.o \
				$(PRINTF_OBJS_DIR)/print_utils.o \
				$(PRINTF_OBJS_DIR)/print_characters.o \
				$(PRINTF_OBJS_DIR)/print_decimal_int.o \
				$(PRINTF_OBJS_DIR)/print_hex_int.o \
				$(PRINTF_OBJS_DIR)/print_decimal_float.o \
				$(PRINTF_OBJS_DIR)/print_hex_float.o \
				$(PRINTF_OBJS_DIR)/print_others.o \
				$(PRINTF_OBJS_DIR)/print_wide_characters.o \
				$(PRINTF_OBJS_DIR)/utf8_helper.o \
				$(PRINTF_OBJS_DIR)/checks_0.o \
				$(PRINTF_OBJS_DIR)/checks_1.o \
				$(PRINTF_OBJS_DIR)/ft_itoa_base.o

PRINTF_DEPDIR := $(PRINTF_PATH)/.deps
PRINTF_DEPFLAGS = -MT $@ -MMD -MP -MF $(PRINTF_DEPDIR)/$*.Td
PRINTF_POSTCOMPILE = mv -f $(PRINTF_DEPDIR)/$*.Td $(PRINTF_DEPDIR)/$*.dep && touch $@
