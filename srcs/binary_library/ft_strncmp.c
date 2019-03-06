/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 09:57:25 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/06 14:59:50 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <binary_loader.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2 && --n)
	{
		if (*s1 == '\0')
			break ;
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int64_t		ft_pow(int64_t base, uint64_t exponent)
{
	uint64_t	i;
	int64_t res;

	i = 0;
	res = 1;
	while (i < exponent)
	{
		res *= base;
		++i;
	}
	return (res);
}

int32_t	ft_natoi(const char *val, size_t size)
{
	size_t	i;
	int64_t	res;

	if (!val)
		return (0);
	i = 0;
	while (i < size && ft_isdigit(val[i]))
		++i;
	size = i;
	i = 0;
	res = 0;
	while (i < size)
	{
		if (!ft_isdigit(val[i]))
			break ;
		res += (val[i] - 48) * ft_pow(10, size - i - 1);
		++i;
	}
	return (res);
}
