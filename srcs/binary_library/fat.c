/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 20:04:39 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int	fat(const void *file, size_t file_size, int is_big_endian)
{
	const t_fat_header	*header;
	const t_fat_arch	*arch;
	uint32_t			i;
	uint32_t			size;


	(void)file_size;
	header = file;
	arch = (void *)header + sizeof(header);
	i = 0;
	size = endianless(is_big_endian, header->nfat_arch);
	while (i < size)
	{
		printf("NEW ARCH\n");
		choose_type(file + endianless(is_big_endian, arch->offset),
				endianless(is_big_endian, arch->size));
		++arch;
		if (!is_in_file(arch, sizeof(t_fat_arch), file, file_size))
			return (0);
		++i;
	}
	return (1);
}
