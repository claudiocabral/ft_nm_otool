/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wide_characters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:06:25 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:55:44 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <modifiers.h>
#include <print.h>
#include <makers.h>
#include <getters.h>

static int	check_wide_char(wchar_t *value, long size)
{
	long	i;

	i = 0;
	while (i < size)
	{
		if (value[i] < 0 || value[i] > 0x10FFFF
				|| ((value[i] >= 0xDC00 && value[i] <= 0xDFFF))
				|| (value[i] >= 0xD800 && value[i] <= 0xDBFF))
			return (i);
		++i;
	}
	return (i);
}

char const	*print_wide_char(char const *format, t_modifiers *modifiers)
{
	char	str[5];
	int		size;
	wchar_t	value;

	value = va_arg(modifiers->args, wchar_t);
	if (!check_wide_char(&value, 1))
		return (0);
	size = wide_char_to_string(value, str);
	print_with_padding(str, modifiers, size);
	return (format);
}

size_t		ft_wstrlen(wchar_t const *str)
{
	size_t	size;
	int		i;
	char	buff[4];

	size = 0;
	i = 0;
	while (str[i])
	{
		size += wide_char_to_string(str[i], buff);
		++i;
	}
	return (size);
}

void		wide_string_to_multibyte(char *str, wchar_t const *value,
		size_t size, size_t precision)
{
	size_t	i;
	size_t	j;
	size_t	nbr_bytes;
	char	buffer[4];

	i = 0;
	while (i < size)
	{
		nbr_bytes = wide_char_to_string(*value++, buffer);
		j = 0;
		if (i + nbr_bytes > precision)
			break ;
		while (j < nbr_bytes)
		{
			str[i + j] = buffer[j];
			++j;
		}
		i += j;
	}
	str[i] = 0;
}

char const	*print_wide_string(char const *format, t_modifiers *modifiers)
{
	char		*str;
	wchar_t		*value;
	size_t		size;

	if (!(value = va_arg(modifiers->args, wchar_t *)))
	{
		print_string_helper("(null)", modifiers);
		return (format);
	}
	size = ft_wstrlen(value);
	size = check_wide_char(value, size);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (format);
	wide_string_to_multibyte(str, value, size,
			(unsigned int)modifiers->precision);
	print_string_helper(str, modifiers);
	free(str);
	return (format);
}
