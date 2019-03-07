/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/07 11:24:08 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int			single_architecture(t_file file, const t_fat_arch *arch,
									int is_big_endian, t_func f)
{
	file.ptr += endianless(is_big_endian, arch->offset);
	file.size = endianless(is_big_endian, arch->size);
	ft_printf("%s:\n", file.name);
	return (f(file, is_big_endian, NULL, 0));
}

const char	*get_cpu_type(cpu_type_t type)
{
	if (type == CPU_TYPE_POWERPC)
		return ("ppc");
	else if (type == CPU_TYPE_POWERPC64)
		return ("ppc64");
	else if (type == CPU_TYPE_I386)
		return ("i386");
	else if (type == CPU_TYPE_MC680x0)
		return ("mc680x0");
	else if (type == CPU_TYPE_MC98000)
		return ("mc98000");
	else if (type == CPU_TYPE_MC88000)
		return ("mc88000");
	else if (type == CPU_TYPE_HPPA)
		return ("hppa");
	else if (type == CPU_TYPE_ARM)
		return ("arm");
	else if (type == CPU_TYPE_ARM64)
		return ("arm64");
	else if (type == CPU_TYPE_SPARC)
		return ("sparc");
	else if (type == CPU_TYPE_I860)
		return ("i860");
	return ("x86_64");
}

void		print_architecture(const t_fat_arch *arch,
				int is_big_endian, const char *filename, int skip_line)
{
	const char	*arch_name;
	cpu_type_t	type;

	type = endianless(is_big_endian, arch->cputype);
	arch_name = get_cpu_type(type);
	if (skip_line)
		ft_printf("\n%s (for architecture %s):\n", filename, arch_name);
	else
		ft_printf("%s (architecture %s):\n", filename, arch_name);
}

int			fat_handler(t_file file, int is_big_endian, int is_otool, t_func f)
{
	t_fat				fat;
	uint32_t			i;

	fat.header = (const t_fat_header *)file.ptr;
	fat.arch = (void *)fat.header + sizeof(t_fat_header);
	fat.is_big_endian = is_big_endian;
	fat.is_otool = is_otool;
	if (!is_in_file(fat.header, sizeof(t_fat_header), file))
		return (0);
	fat.nbr_archs = endianless(is_big_endian, fat.header->nfat_arch);
	if (!is_in_file(fat.arch, sizeof(t_fat_arch) * fat.nbr_archs, file))
		return (0);
	if (try_native(&fat, file, f))
		return (1);
	i = 0;
	while (i < fat.nbr_archs)
	{
		print_architecture(fat.arch + i, is_big_endian, file.name, !is_otool);
		if (!(apply_to_architecture(&fat, file, i, f)))
			return (0);
		++i;
	}
	return (1);
}

int			fat_endianless(t_file file, int is_otool, t_func f)
{
	uint32_t	magic_number;

	if (file.size < sizeof(int))
		return (1);
	magic_number = *(int *)file.ptr;
	if (magic_number == FAT_CIGAM)
		return (fat_handler(file, 1, is_otool, f));
	else if (magic_number == FAT_MAGIC)
		return (fat_handler(file, 0, is_otool, f));
	return (NOT_FAT);
}
