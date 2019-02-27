/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:01:40 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/11 16:56:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include "modifiers.h"
#include "percent.h"
#include "flags.h"
#include "checks.h"
#include "utils.h"

char const	*star_field_width(char const *format, t_modifiers *modifiers)
{
	int	val;

	val = va_arg(modifiers->args, int);
	if (val < 0)
	{
		modifiers->flags |= MINUS;
		val = -val;
	}
	modifiers->field_width = val;
	return (format + 1);
}

char const	*flag(char const *format, t_modifiers *modifiers)
{
	if (*format == '#')
		modifiers->flags |= HASHTAG;
	else if (*format == '0')
		modifiers->flags |= ZERO;
	else if (*format == '-')
		modifiers->flags |= MINUS;
	else if (*format == '+')
		modifiers->flags |= PLUS;
	else if (*format == ' ')
		modifiers->flags |= SPACE;
	return (format + 1);
}

char const	*field_width(char const *format, t_modifiers *modifiers)
{
	int	num;

	num = 0;
	while (is_digit(*format))
	{
		num *= 10;
		num += *format - '0';
		++format;
	}
	modifiers->field_width = num;
	return (format);
}

char const	*precision(char const *format, t_modifiers *modifiers)
{
	int	num;

	num = 0;
	++format;
	while (is_digit(*format))
	{
		num *= 10;
		num += *format - '0';
		++format;
	}
	modifiers->precision = num;
	return (format);
}

char const	*length(char const *format, t_modifiers *modifiers)
{
	if (*format == 'h' && format[1] == 'h')
	{
		++format;
		modifiers->length = ftprintf_max(modifiers->length, HH);
	}
	else if (*format == 'h')
		modifiers->length = ftprintf_max(modifiers->length, H);
	else if (*format == 'l' && format[1] == 'l')
	{
		++format;
		modifiers->length = ftprintf_max(modifiers->length, LL);
	}
	else
		modifiers->length = ftprintf_max(modifiers->length, L);
	++format;
	return (format);
}
