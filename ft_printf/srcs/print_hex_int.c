/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 14:36:46 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/02 22:04:48 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modifiers.h"
#include "print.h"
#include "utils.h"
#include "getters.h"
#include <stdlib.h>

static void			print_int_hex_helper(char const *str, char const *prefix,
														t_modifiers *modifiers)
{
	size_t	size;
	int		padding;
	int		precision;

	size = ftprintf_strlen(str);
	precision = ftprintf_max(modifiers->precision, ftprintf_strlen(str));
	padding = modifiers->field_width - ftprintf_max(precision, size)
									- ftprintf_strlen(prefix);
	if ((*str == '0' && modifiers->precision == 0))
		padding += 1;
	if (!(modifiers->flags & MINUS) && !(modifiers->flags & ZERO))
		print_padding(padding, 0, modifiers->fd);
	write_and_count(modifiers->fd, prefix, ftprintf_strlen(prefix));
	if (!(modifiers->flags & MINUS) && (modifiers->flags & ZERO))
		print_padding(padding, modifiers->precision == -1, modifiers->fd);
	print_padding(precision - size, 1, modifiers->fd);
	if (!(*str == '0' && modifiers->precision == 0))
		write_and_count(modifiers->fd, str, ftprintf_strlen(str));
	if ((modifiers->flags & MINUS))
		print_padding(padding, 0, modifiers->fd);
}

char const			*print_big_int_hex(char const *format,
		t_modifiers *modifiers)
{
	unsigned long	value;
	char			*str;
	char			*prefix;

	value = get_unsigned_int(modifiers);
	if (!(str = ftprintf_itoa_base(value, "0123456789ABCDEF")))
		return (format);
	if ((modifiers->flags & HASHTAG) && value != 0)
		prefix = "0X";
	else
		prefix = "";
	print_int_hex_helper(str, prefix, modifiers);
	free(str);
	return (format);
}

char const			*print_small_int_hex(char const *format,
		t_modifiers *modifiers)
{
	unsigned long	value;
	char			*str;
	char			*prefix;

	value = get_unsigned_int(modifiers);
	if (!(str = ftprintf_itoa_base(value, "0123456789abcdef")))
		return (format);
	if ((modifiers->flags & HASHTAG) && value != 0)
		prefix = "0x";
	else
		prefix = "";
	print_int_hex_helper(str, prefix, modifiers);
	free(str);
	return (format);
}
