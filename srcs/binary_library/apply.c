/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:07:21 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/07 10:33:36 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>
#include <sys/mman.h>
#include <unistd.h>

int	apply_to_file(const char *filename, t_func f, int multiple, int is_otool)
{
	t_file			file;
	int				res;

	if (!(map_file(filename, &file)))
		return (1);
	if ((res = fat_endianless(file, is_otool, f)) != NOT_FAT)
	{
		munmap((void *)file.ptr, file.size);
		return (!res);
	}
	if ((res = parse_static_library(file, f, is_otool) != NOT_FAT))
	{
		munmap((void *)file.ptr, file.size);
		return (!res);
	}
	if (multiple)
		ft_printf("\n%s:\n", filename);
	res = f(file, 0, NULL, 0);
	munmap((void *)file.ptr, file.size);
	return (!res);
}

int	apply_to_lib(t_file file, t_func f, int is_otools)
{
	int	res;

	if ((res = parse_static_library(file, f, is_otools)) != NOT_FAT)
		return (!res);
	return (f(file,  0, 0, 0));
}

int	apply_to_architecture(t_fat *fat, t_file file, int index, t_func f)
{
	file.ptr += endianless(fat->is_big_endian, fat->arch[index].offset);
	file.size = endianless(fat->is_big_endian, fat->arch[index].size);
	return (apply_to_lib(file, f, fat->is_otool));
}
