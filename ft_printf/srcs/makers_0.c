/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makers_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:25:37 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:26:20 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <makers.h>
#include <checks.h>
#include <utils.h>

int		add_sign(char *str, int sign, t_modifiers *modifiers)
{
	if (is_unsigned_int(modifiers->type))
		return (0);
	else if (sign == -1)
		*str = '-';
	else if (modifiers->flags & PLUS)
		*str = '+';
	else if (modifiers->flags & SPACE)
		*str = ' ';
	else
		return (0);
	return (1);
}

char	*make_hex_string(unsigned long long value, char const *const hex_set,
												t_modifiers *modifiers)
{
	char	str[64];
	int		i;

	str[63] = 0;
	i = 62;
	while (1)
	{
		str[i--] = hex_set[value % 16];
		value /= 16;
		if (!value)
			break ;
	}
	while (62 - i < modifiers->precision)
		str[i--] = '0';
	return (ft_strdup(str + i + 1));
}

char	*make_octal_string(unsigned long long value, t_modifiers *modifiers)
{
	static char const	*oct_set = "01234567";
	char				str[64];
	int					i;
	int					not_zero;

	str[63] = 0;
	if (modifiers->precision == 0 && value == 0
			&& !(modifiers->flags & HASHTAG))
		return (ft_strdup(""));
	i = 62;
	not_zero = value != 0;
	while (1)
	{
		str[i--] = oct_set[value % 8];
		value /= 8;
		if (!value)
			break ;
	}
	while (62 - i < modifiers->precision)
		str[i--] = '0';
	if (str[i + 1] != '0' && not_zero && (modifiers->flags & HASHTAG))
		str[i--] = '0';
	return (ft_strdup(str + i + 1));
}

char	*make_decimal_string(unsigned long long value, int sign,
		t_modifiers *modifiers)
{
	char	str[64];
	int		i;

	if (modifiers->precision == 0 && value == 0)
		return (ft_strdup(""));
	str[63] = 0;
	i = 62;
	while (1)
	{
		str[i--] = value % 10 + '0';
		value /= 10;
		if (!value)
			break ;
	}
	while (62 - i < modifiers->precision)
		str[i--] = '0';
	i -= add_sign(str + i, sign, modifiers);
	return (ft_strdup(str + i + 1));
}
