/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:55:59 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/04 15:33:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int		try_native(t_file file, const t_fat_arch *arch,
			uint32_t size, int is_big_endian, t_func f)
{
	uint32_t	i;
	cpu_type_t	type;

	i = 0;
	while (i < size)
	{
		type = endianless(is_big_endian, arch[i].cputype);
		if (type == CPU_TYPE_X86_64)
		{
			file.ptr += endianless(is_big_endian, arch[i].offset);
			file.size = endianless(is_big_endian, arch[i].size);
			return (f(file, is_big_endian, NULL));
		}
		++i;
	}
	return (0);
}

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
		return (1);
	size = endianless(is_big_endian, header->nfat_arch);
	if (!is_in_file(arch, sizeof(t_fat_arch) * size, file))
		return (1);
	if (try_native(file, arch, size, is_big_endian, f))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(f(file, is_big_endian, arch + i++)))
			return (1);
	}
	return (0);
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
