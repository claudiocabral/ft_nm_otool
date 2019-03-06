/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/06 16:54:36 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int		single_architecture(t_file file, const t_fat_arch *arch,
									int is_big_endian, t_func f)
{
	file.ptr += endianless(is_big_endian, arch->offset);
	file.size = endianless(is_big_endian, arch->size);
	ft_printf("%s:\n", file.name);
	return (f(file, is_big_endian, NULL, 0));
}

int		try_native(t_file file, const t_fat_arch *arch,
		uint32_t size, int is_big_endian, t_func f)
{
	uint32_t	i;
	cpu_type_t	type;

	i = 0;
	if (size == 1)
		return (single_architecture(file, arch, is_big_endian, f));
	while (i < size)
	{
		type = endianless(is_big_endian, arch[i].cputype);
		if (type == CPU_TYPE_X86_64)
		{
			file.ptr += endianless(is_big_endian, arch[i].offset);
			file.size = endianless(is_big_endian, arch[i].size);
			return (f(file, is_big_endian, NULL, 0));
		}
		++i;
	}
	return (0);
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

void	print_architecture(const t_fat_arch *arch, int is_big_endian,
		const char *filename, int skip_line)
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

int		fat(t_file file, int is_big_endian, t_func f)
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
	if (try_native(file, arch, size, is_big_endian, f))
		return (1);
	i = 0;
	while (i < size)
	{
		if (!(f(file, is_big_endian, arch + i++, 0)))
			return (0);
	}
	return (1);
}

int		fat_endianless(t_file file, t_func f)
{
	uint32_t	magic_number;

	if (file.size < sizeof(int))
		return (1);
	magic_number = *(int *)file.ptr;
	if (magic_number == FAT_CIGAM)
		return (fat(file, 1, f));
	else if (magic_number == FAT_MAGIC)
		return (fat(file, 0, f));
	return (NOT_FAT);
}
