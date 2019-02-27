/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:04:09 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 14:55:23 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int		hexdump_32_packed(const char *buffer, uint32_t size, uint32_t address)
{
	int			i;
	uint32_t	offset;

	offset = 0;
	while (offset < size)
	{
		ft_printf("%08x\t", offset + address);
		i = 0;
		while (i < 16 && offset + i < size)
		{
			ft_puthex(buffer[offset + i]);
			if (!((i + 1) % 4))
				ft_printf(" ");
			++i;
		}
		ft_printf("\n");
		offset += i;
	}
	return (1);
}

int		hexdump_32(const char *buffer, uint32_t size, uint32_t address)
{
	int			i;
	uint32_t	offset;

	offset = 0;
	while (offset < size)
	{
		ft_printf("%08x\t", offset + address);
		i = 0;
		while (i < 16 && offset + i < size)
		{
			ft_puthex(buffer[offset + i]);
			ft_printf(" ");
			++i;
		}
		ft_printf("\n");
		offset += i;
	}
	return (1);
}

int		hexdump(const char *buffer, uint64_t size, uint64_t address)
{
	uint64_t	i;
	uint64_t	offset;

	offset = 0;
	while (offset < size)
	{
		ft_printf("%016llx\t", offset + (uint64_t)address);
		i = 0;
		while (i < 16 && offset + i < size)
		{
			ft_puthex(buffer[offset + i]);
			ft_printf(" ");
			++i;
		}
		ft_printf("\n");
		offset += i;
	}
	return (1);
}
