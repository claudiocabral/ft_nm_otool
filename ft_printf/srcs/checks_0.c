/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:21:19 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:22:06 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checks.h>

int	is_signed_int(t_type type)
{
	if (type == SIGNED_DECIMAL)
		return (1);
	return (0);
}

int	is_unsigned_int(t_type type)
{
	if (type == UNSIGNED_DECIMAL || type == OCTAL
			|| type == BIG_HEX || type == SMALL_HEX)
		return (1);
	return (0);
}

int	is_float(t_type type)
{
	if (type == EXPONENTIAL_BIG_DOUBLE || type == EXPONENTIAL_SMALL_DOUBLE
			|| type == DECIMAL_DOUBLE || type == VARIABLE_STYLE_BIG_DOUBLE
			|| type == VARIABLE_STYLE_SMALL_DOUBLE || type == DOUBLE_BIG_HEX
			|| type == DOUBLE_SMALL_HEX)
		return (1);
	return (0);
}

int	is_character(t_type type)
{
	if (type == CHAR || type == WIDE_CHAR)
		return (1);
	return (0);
}

int	is_string(t_type type)
{
	if (type == STRING || type == WIDE_STRING)
		return (1);
	return (0);
}
