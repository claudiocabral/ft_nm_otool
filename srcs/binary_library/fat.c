/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/26 13:05:20 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	print_architecture(const t_fat_arch *arch, int is_big_endian,
											const char *filename)
{
	const char	*arch_name;
	cpu_type_t	type;


	type = endianless(is_big_endian, arch->cputype);
	if (type == CPU_TYPE_POWERPC)
		arch_name = "ppc";
	else if (type == CPU_TYPE_I386)
		arch_name = "i386";
	printf("\n%s (for architecture %s):\n", filename, arch_name);
}

int	fat(const void *file, size_t file_size, const char *filename,
												int is_big_endian)
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
		if (!is_in_file(arch, sizeof(t_fat_arch), file, file_size))
			return (0);
		print_architecture(arch, is_big_endian, filename);
		choose_type(file + endianless(is_big_endian, arch->offset),
				endianless(is_big_endian, arch->size), filename);
		++arch;
		++i;
	}
	return (1);
}
