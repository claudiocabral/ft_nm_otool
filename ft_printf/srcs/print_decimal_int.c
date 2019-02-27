/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:46:33 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/02 22:03:58 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modifiers.h"
#include "print.h"
#include "utils.h"
#include "getters.h"
#include <stdlib.h>

void			print_decimal_helper(char const *str, char sign,
									t_modifiers *modifiers)
{
	size_t	size;
	int		precision;
	int		padding;

	size = ftprintf_strlen(str);
	precision = modifiers->precision - size;
	if (precision < 0)
		precision = 0;
	padding = modifiers->field_width - size - precision - (sign != 0);
	if ((*str == '0' && modifiers->precision == 0))
		++padding;
	if (!(modifiers->flags & MINUS) && !(modifiers->flags & ZERO))
		print_padding(padding, 0, modifiers->fd);
	if (modifiers->precision == -1)
		write_and_count(modifiers->fd, &sign, sign != 0);
	if (!(modifiers->flags & MINUS) && (modifiers->flags & ZERO))
		print_padding(padding, modifiers->precision == -1, modifiers->fd);
	if (modifiers->precision != -1)
		write_and_count(modifiers->fd, &sign, sign != 0);
	print_padding(modifiers->precision - size, 1, modifiers->fd);
	if (!(*str == '0' && modifiers->precision == 0))
		write_and_count(modifiers->fd, str, ftprintf_strlen(str));
	if ((modifiers->flags & MINUS))
		print_padding(padding, 0, modifiers->fd);
}

char const		*print_signed_decimal(char const *format,
		t_modifiers *modifiers)
{
	long			value;
	char			*str;
	char			sign;

	value = get_signed_int(modifiers);
	sign = get_number_sign(value, modifiers);
	value = (value < 0) ? -((long)value) : value;
	if (!(str = ftprintf_itoa_base(value, "0123456789")))
		return (format);
	print_decimal_helper(str, sign, modifiers);
	free(str);
	return (format);
}

char const		*print_unsigned_decimal(char const *format,
		t_modifiers *modifiers)
{
	unsigned long	value;
	char			*str;

	value = get_unsigned_int(modifiers);
	if (!(str = ftprintf_itoa_base(value, "0123456789")))
		return (format);
	print_decimal_helper(str, 0, modifiers);
	free(str);
	return (format);
}

char const		*print_octal(char const *format,
		t_modifiers *modifiers)
{
	unsigned long	value;
	char			*str;
	int				precision;
	int				size;

	value = get_unsigned_int(modifiers);
	if (!(str = ftprintf_itoa_base(value, "01234567")))
		return (format);
	size = ftprintf_strlen(str);
	precision = ftprintf_max(modifiers->precision, size);
	if ((modifiers->flags & HASHTAG) && *str != '0')
		precision += (precision == size);
	if ((*str == '0' && modifiers->precision == 0))
		--precision;
	if (!(modifiers->flags & MINUS))
		print_padding(modifiers->field_width - precision, modifiers->flags
				& ZERO && modifiers->precision == -1, modifiers->fd);
	print_padding(precision - size, 1, modifiers->fd);
	if (modifiers->flags & HASHTAG
			|| !(*str == '0' && modifiers->precision == 0))
		write_and_count(modifiers->fd, str, ftprintf_strlen(str));
	if ((modifiers->flags & MINUS))
		print_padding(modifiers->fd, modifiers->field_width - precision, 0);
	free(str);
	return (format);
}
