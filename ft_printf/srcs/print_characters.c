/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_characters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:36:33 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/02 22:01:45 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <print.h>
#include <utils.h>
#include <getters.h>

char const			*print_char(char const *format, t_modifiers *modifiers)
{
	char	c;

	if (modifiers->length >= L)
		return (print_wide_char(format, modifiers));
	c = (char)va_arg(modifiers->args, int);
	print_with_padding(&c, modifiers, 1);
	return (format);
}

void				print_string_helper(char const *str, t_modifiers *modifiers)
{
	long	size;
	long	padding;

	if (modifiers->precision >= 0)
		size = ftprintf_min(ftprintf_strlen(str), modifiers->precision);
	else
		size = ftprintf_strlen(str);
	padding = modifiers->field_width - size;
	if (!(modifiers->flags & MINUS))
		print_padding(padding, modifiers->flags & ZERO, modifiers->fd);
	write_and_count(modifiers->fd, str, size);
	if ((modifiers->flags & MINUS))
		print_padding(padding, 0, modifiers->fd);
}

char const			*print_string(char const *format, t_modifiers *modifiers)
{
	char	*str;

	if (modifiers->length >= L)
		return (print_wide_string(format, modifiers));
	if (!(str = va_arg(modifiers->args, char *)))
		str = "(null)";
	print_string_helper(str, modifiers);
	return (format);
}
