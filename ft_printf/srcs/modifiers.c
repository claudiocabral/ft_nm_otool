/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:24:36 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/02 21:59:58 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modifiers.h"

void		init_modifiers(t_modifiers *modifiers, int fd, va_list *args)
{
	modifiers->type = NULL_T;
	modifiers->flags = NO_FLAGS;
	modifiers->precision = -1;
	modifiers->field_width = -1;
	modifiers->arg_number = 0;
	modifiers->length = NONE;
	modifiers->separator = 0;
	modifiers->separator_size = 0;
	modifiers->fd = fd;
	va_copy(modifiers->args, *args);
}

void		clean_modifiers(t_modifiers *modifiers)
{
	va_end(modifiers->args);
}

void		reset_modifiers(t_modifiers *modifiers)
{
	modifiers->type = NULL_T;
	modifiers->flags = NO_FLAGS;
	modifiers->precision = -1;
	modifiers->field_width = -1;
	modifiers->arg_number = 0;
	modifiers->length = NONE;
	modifiers->separator = 0;
	modifiers->separator_size = 0;
}
