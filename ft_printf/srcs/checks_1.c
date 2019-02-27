/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:17:32 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:22:49 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checks.h>

int	is_int_type(char c)
{
	if (c == 'd' || c == 'D' || c == 'o' || c == 'O' || c == 'x' || c == 'X'
			|| c == 'u' || c == 'U' || c == 'i')
		return (1);
	return (0);
}

int	is_float_type(char c)
{
	if (c == 'f' || c == 'F' || c == 'e' || c == 'E'
			|| c == 'g' || c == 'G' || c == 'a' || c == 'A')
		return (1);
	return (0);
}

int	is_char_type(char c)
{
	if (c == 'c' || c == 'C')
		return (1);
	return (0);
}

int	is_string_type(char c)
{
	if (c == 's' || c == 'S')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
