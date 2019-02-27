/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:44:00 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 15:33:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int			ft_strcmp_safe(const char *s1, const char *s2, const char *eof)
{
	while (s1 < eof && s2 < eof && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	if (s1 > eof || s2 > eof)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int			ft_strcmp_s1_check(const char *s1, const char *s2,
												const char *eof)
{
	while (s1 < eof && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	if (s1 >= eof)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

uint32_t	big_to_little_endian(uint32_t val)
{
	return ((((val) & 0xff000000) >> 24)
			| (((val) & 0xff0000) >> 8)
			| (((val) & 0xff00) << 8)
			| (((val) & 0xff) << 24));
}

uint32_t	endianless(int is_big_endian, uint32_t val)
{
	if (is_big_endian)
		return (big_to_little_endian(val));
	return (val);
}

int			is_in_file(const void *ptr, size_t size, t_file file)
{
	return ((const uint8_t *)ptr + size < file.ptr + file.size
			&& (const uint8_t *)ptr + size > file.ptr);
}
