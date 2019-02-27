/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:24:45 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:55:42 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <sys/types.h>
#include <stddef.h>
#include <getters.h>
#include <wchar.h>

long			get_signed_int(t_modifiers *modifiers)
{
	long	value;

	if (modifiers->length == NONE)
		value = va_arg(modifiers->args, int);
	else if (modifiers->length == HH)
		value = (char)va_arg(modifiers->args, int);
	else if (modifiers->length == H)
		value = (short)va_arg(modifiers->args, int);
	else
		value = va_arg(modifiers->args, long long);
	return (value);
}

unsigned long	get_unsigned_int(t_modifiers *modifiers)
{
	unsigned long	value;

	if (modifiers->length == NONE)
		value = va_arg(modifiers->args, unsigned int);
	else if (modifiers->length == HH)
		value = (unsigned char)va_arg(modifiers->args, unsigned int);
	else if (modifiers->length == H)
		value = (unsigned short)va_arg(modifiers->args, unsigned int);
	else
		value = va_arg(modifiers->args, unsigned long long);
	return (value);
}

t_data			get_character(t_modifiers *modifiers)
{
	t_data	value;

	if (modifiers->type == CHAR)
		value.c = va_arg(modifiers->args, int);
	else
		value.wc = va_arg(modifiers->args, wint_t);
	return (value);
}
