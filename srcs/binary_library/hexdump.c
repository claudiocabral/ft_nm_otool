/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:04:09 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 13:44:45 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	ft_print_addr(long c)
{
	char	*hex;
	long	val;
	long	tmp;

	hex = "0123456789abcdef";
	val = 0x1;
	tmp = c / 0x10;
	while (tmp || val < 0x10000000)
	{
		tmp /= 0x10;
		val *= 0x10;
	}
	while (val)
	{
		printf("%c", hex[c / val]);
		c %= val;
		val /= 0x10;
	}
}

int		hexdump(const char *buffer, uint64_t size, uint64_t address)
{
	int			i = 0;
	uint64_t	offset = 0;

	(void)buffer;
	while (offset < size)
	{
		printf("%016llx\t", offset + (uint64_t)address);
		i = 0;
		while (i < 16 && offset + i < size)
		{
			ft_puthex(buffer[offset + i]);
			printf(" ");
			++i;
		}
		printf("\n");
		offset += i;
	}
	return (1);
}
