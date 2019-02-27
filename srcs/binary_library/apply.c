/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:07:21 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 16:15:33 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>
#include <sys/mman.h>
#include <unistd.h>

int	apply_to_file(const char *filename, t_func f, int multiple)
{
	t_file			file;
	int				res;

	if (!(map_file(filename, &file)))
		return (1);
	if ((res = fat_endianless(file, f)) == NOT_FAT)
	{
		if (multiple)
			ft_printf("\n%s:\n", filename);
		res = f(file, 0, NULL);
	}
	munmap((void *)file.ptr, file.size);
	return (res);
}
