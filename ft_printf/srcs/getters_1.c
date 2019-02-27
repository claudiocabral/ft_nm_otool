/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:23:41 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:55:42 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getters.h"

t_data	get_float_value(t_modifiers *modifiers)
{
	t_data	value;

	set_argument(modifiers);
	if (modifiers->length == BIG_L)
		value.f = va_arg(modifiers->args, long double);
	else
		value.f = va_arg(modifiers->args, double);
	return (value);
}

t_data	get_string(t_modifiers *modifiers)
{
	t_data	value;

	if (modifiers->type == WIDE_STRING || modifiers->length == L)
		value.ws = va_arg(modifiers->args, wchar_t *);
	else
		value.s = va_arg(modifiers->args, char *);
	return (value);
}

t_data	get_pointer(t_modifiers *modifiers)
{
	t_data	value;
	void	*pointer;

	set_argument(modifiers);
	pointer = va_arg(modifiers->args, void *);
	value.ull = (unsigned long)pointer;
	modifiers->flags |= HASHTAG;
	return (value);
}
