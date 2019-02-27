/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:01:35 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:55:44 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "modifiers.h"

char const	*wild_card(char const *format, t_modifiers *modifiers)
{
	modifiers->field_width = va_arg(modifiers->args, int);
	return (format);
}
