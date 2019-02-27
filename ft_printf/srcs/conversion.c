/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:26:49 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 18:00:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <percent.h>
#include <modifiers.h>
#include <checks.h>
#include <print.h>

static t_type	get_int_type(char c)
{
	if (c == 'd' || c == 'D')
		return (SIGNED_DECIMAL);
	else if (c == 'u' || c == 'U')
		return (UNSIGNED_DECIMAL);
	else if (c == 'o' || c == 'O')
		return (OCTAL);
	else if (c == 'x')
		return (SMALL_HEX);
	else if (c == 'X')
		return (BIG_HEX);
	return (SIGNED_DECIMAL);
}

static t_type	get_float_type(char c)
{
	if (c == 'f' || c == 'F')
		return (DECIMAL_DOUBLE);
	else if (c == 'e')
		return (EXPONENTIAL_SMALL_DOUBLE);
	else if (c == 'E')
		return (EXPONENTIAL_BIG_DOUBLE);
	else if (c == 'g')
		return (VARIABLE_STYLE_SMALL_DOUBLE);
	else if (c == 'G')
		return (VARIABLE_STYLE_BIG_DOUBLE);
	else if (c == 'a')
		return (DOUBLE_SMALL_HEX);
	else if (c == 'A')
		return (DOUBLE_BIG_HEX);
	return (DECIMAL_DOUBLE);
}

static t_type	get_char_type(char c)
{
	if (c == 'c')
		return (CHAR);
	else if (c == 'C')
		return (WIDE_CHAR);
	else if (c == 's')
		return (STRING);
	else if (c == 'S')
		return (WIDE_STRING);
	return (CHAR);
}

char const		*conversion(char const *format, t_modifiers *modifiers)
{
	char	c;

	c = *format;
	if (is_int_type(c))
	{
		modifiers->type = get_int_type(c);
		if (c == 'D' || c == 'O' || c == 'U')
			modifiers->length = L;
	}
	else if (is_float_type(c))
		modifiers->type = get_float_type(c);
	else if (is_char_type(c) || is_string_type(c))
		modifiers->type = get_char_type(c);
	else if (c == 'p')
		modifiers->type = POINTER;
	else if (c == 'n')
		modifiers->type = STORAGE;
	else
		return (format);
	return (format + 1);
}
