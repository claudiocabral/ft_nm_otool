/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:47:14 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/02 22:05:31 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "getters.h"
#include "utils.h"
#include <stdlib.h>

static void			pointer_helper(char const *str, t_modifiers *modifiers,
															int padding)
{
	int	precision;

	precision = (modifiers->precision < 0) ? 0 : modifiers->precision;
	if (!(modifiers->flags & MINUS) && !(modifiers->flags & ZERO))
		print_padding(padding, 0, modifiers->fd);
	write_and_count(modifiers->fd, "0x", 2);
	print_padding(precision - ftprintf_strlen(str), 1, modifiers->fd);
	if (!(modifiers->flags & MINUS) && (modifiers->flags & ZERO))
		print_padding(padding, 1, modifiers->fd);
	if (modifiers->precision != 0 || *str != '0')
		write_and_count(modifiers->fd, str, ftprintf_strlen(str));
	if ((modifiers->flags & MINUS))
		print_padding(padding, 0, modifiers->fd);
}

char const			*print_pointer(char const *format, t_modifiers *modifiers)
{
	unsigned long	value;
	char			*str;
	int				padding;
	int				precision;

	value = va_arg(modifiers->args, unsigned long);
	if (!(str = ftprintf_itoa_base(value, "0123456789abcdef")))
		return (format);
	precision = ftprintf_max(modifiers->precision, ftprintf_strlen(str));
	padding = modifiers->field_width - precision - 2;
	pointer_helper(str, modifiers, padding);
	free(str);
	return (format);
}

char const			*store_value(char const *format, t_modifiers *modifiers)
{
	int	*value;

	value = va_arg(modifiers->args, int *);
	*value = get_character_count();
	return (format);
}

char const			*print_invalid(char const *format,
		t_modifiers *modifiers)
{
	if (*format)
		print_with_padding(format++, modifiers, 1);
	return (format);
}

char const			*no_op(char const *format,
		t_modifiers *modifiers)
{
	(void)modifiers;
	return (format);
}
