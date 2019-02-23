/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 19:04:51 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	fat(const void *file, size_t file_size)
{
	const t_fat_header	*header;
	const t_fat_arch	*arch;
	uint32_t			i;
	uint32_t			size;


	(void)file_size;
	header = file;
	arch = (void *)header + sizeof(header);
	i = 0;
	size = big_to_little_endian(header->nfat_arch);
	while (i < size)
	{
		choose_type(file + big_to_little_endian(arch->offset),
				big_to_little_endian(arch->size));
		++arch;
		++i;
	}
}
