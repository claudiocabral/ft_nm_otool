/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 10:51:34 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	print_architecture(const t_fat_arch *arch, int is_big_endian,
		const char *filename, int skip_line)
{
	const char	*arch_name;
	cpu_type_t	type;


	type = endianless(is_big_endian, arch->cputype);
	if (type == CPU_TYPE_POWERPC)
		arch_name = "ppc";
	else if (type == CPU_TYPE_I386)
		arch_name = "i386";
	if (skip_line)
		printf("\n%s (for architecture %s):\n", filename, arch_name);
	else
		printf("%s (for architecture %s):\n", filename, arch_name);
}

int		nm_body(t_file file, int is_big_endian, t_fat_arch *arch)
{
	t_abstract_mach	header;

	if (arch)
	{
		print_architecture(arch, is_big_endian, file.name, 1);
		file.ptr += endianless(is_big_endian, arch->offset);
		file.size = endianless(is_big_endian, arch->size);
	}
	header = choose_type(file);
	if (!header.file.ptr)
		return (0);
	parse(&header);
	return (1);
}

int	fat(t_file file, int is_big_endian, t_func f)
{
	const t_fat_header	*header;
	const t_fat_arch	*arch;
	uint32_t			i;
	uint32_t			size;


	header = (const t_fat_header *)file.ptr;
	arch = (void *)header + sizeof(header);
	if (!is_in_file(header, sizeof(t_fat_header), file))
		return (0);
	size = endianless(is_big_endian, header->nfat_arch);
	if (!is_in_file(arch, sizeof(t_fat_arch) * size, file))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(f(file, is_big_endian, arch)))
			return (0);
		++arch;
		++i;
	}
	return (1);
}

int		fat_endianless(t_file file, t_func f)
{
	uint32_t	magic_number;

	magic_number = *(int *)file.ptr;
	if (magic_number == FAT_CIGAM)
		return fat(file, 1, f);
	else if (magic_number == FAT_MAGIC)
		return fat(file, 0, f);
	return (NOT_FAT);
}
