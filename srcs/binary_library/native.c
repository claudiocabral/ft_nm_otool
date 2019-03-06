/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:27:39 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/06 17:37:22 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

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
		type = endianless(1, arch[i].cputype);
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
