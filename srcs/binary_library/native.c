/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   native.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:27:39 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/08 11:03:13 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int		try_native(t_fat *fat, t_file file, t_func f)
{
	uint32_t	i;
	cpu_type_t	type;

	i = 0;
	if (fat->nbr_archs == 1)
	{
		type = endianless(fat->is_big_endian, fat->arch[0].cputype);
		if (type != CPU_TYPE_X86_64 && !fat->is_otool)
			ft_printf("%s:\n", file.name);
		return (apply_to_architecture(fat, file, 0, f));
	}
	while (i < fat->nbr_archs)
	{
		type = endianless(fat->is_big_endian, fat->arch[i].cputype);
		if (type == CPU_TYPE_X86_64)
			return (apply_to_architecture(fat, file, i, f));
		++i;
	}
	return (0);
}
