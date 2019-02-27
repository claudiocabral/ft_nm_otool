/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf8_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:06:01 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:30:22 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>

static int	count_bits(wchar_t c)
{
	unsigned int	i;

	i = 32;
	while (i > 0 && (c & (1 << (i - 1))) == 0)
		--i;
	return (i);
}

static int	utf8_size(unsigned char c)
{
	if (!(c & 0x80))
		return (1);
	if (!(c & 0x20))
		return (2);
	if (!(c & 0x10))
		return (3);
	return (4);
}

int			wide_char_to_string(wchar_t value, char *str)
{
	int				i;

	i = count_bits(value);
	if (i < 8)
		*str = value;
	else if (i < 12)
	{
		str[0] = 0xc0 | (value >> 6);
		str[1] = 0x80 | (value & 0x3f);
	}
	else if (i < 17)
	{
		str[0] = 0xe0 | ((value >> 12) & 0xf);
		str[1] = 0x80 | ((value >> 6) & 0x3f);
		str[2] = 0x80 | ((value) & 0x3f);
	}
	else
	{
		str[0] = 0xf0 | ((value >> 18) & 7);
		str[1] = 0x80 | ((value >> 12) & 0x3f);
		str[2] = 0x80 | ((value >> 6) & 0x3f);
		str[3] = 0x80 | ((value) & 0x3f);
	}
	return (utf8_size((unsigned char)*str));
}
