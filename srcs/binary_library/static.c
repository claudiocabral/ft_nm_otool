/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:40:53 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/06 16:24:33 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include <binary_loader.h>
#include <unistd.h>

void	print_lib(t_file archive, t_file object)
{
	uint32_t	name_size;

	name_size = 20;
	if (ft_strncmp((const char *)object.name, "#1/", 3) == 0)
	{
		name_size = ft_natoi((const char *)object.name + 3, 13);
		object.name += 60;
	}
	ft_printf("\n%s(%s):\n", archive.name, object.name);
}

t_file	set_file(t_file file)
{
	uint32_t	name_size;
	uint32_t	size;

	name_size = 0;
	if (ft_strncmp((const char *)file.ptr, "#1/", 3) == 0)
		name_size = ft_natoi((const char *)file.ptr + 3, 13);
	name_size = (name_size + (4 - (name_size % 4))) - 4;
	size = ft_natoi((const char *)file.ptr + 48, 8);
	file.name = (const char *)file.ptr;
	file.ptr += 60 + name_size;
	file.size = size - name_size;
	return (file);
}

int	handle_static_library(t_file file, t_func f)
{
	t_file		new_file;
	uint32_t	name_size;
	uint32_t	size;

	name_size = 0;
	if (ft_strncmp((const char *)file.ptr + HEADER, "#1/", 3) == 0)
		name_size = ft_natoi((const char *)file.ptr + 3 + HEADER, 13);
	size = ft_natoi((const char *)file.ptr + 48 + HEADER, 8);
	new_file.ptr = file.ptr + 60 + size + HEADER;
	new_file.size = 60;
	new_file.name = "";
	while (is_in_file(new_file.ptr, new_file.size, file))
	{
		new_file = set_file(new_file);
		print_lib(file, new_file);
		f(new_file, 0, 0);
		new_file.ptr += new_file.size;
		new_file.size = 60;
		if (new_file.ptr == file.ptr + file.size)
			break ;
	}
	return (0);
}

int	parse_static_library(t_file file, t_func f)
{
	if (file.size < 68)
		return (0);
	if (ft_strncmp((const char *)file.ptr, "!<arch>\n", 8) == 0)
		return (handle_static_library(file, f));
	return (NOT_FAT);
}
