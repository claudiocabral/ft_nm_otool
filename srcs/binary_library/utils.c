/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:44:00 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 19:23:29 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
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
		return big_to_little_endian(val);
	return (val);
}
