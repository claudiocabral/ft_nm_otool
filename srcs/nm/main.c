/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:07:21 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 12:04:42 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>
#include <sys/mman.h>
#include <unistd.h>

static int	nm_body(t_file file, int is_big_endian, const t_fat_arch *arch)
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
	return (parse(&header));
}

int			nm(const char *filename)
{
	return (apply_to_file(filename, nm_body));
}

int			nm_error_no_file(void)
{
	write(STDERR_FILENO,
			"error: ft_nm: at least one file must be specified\n",
			50);
	return (1);
}

int			main(int argc, char	**argv)
{
	int	i;
	int	tmp;
	int	res;

	i = 1;
	res = 0;
	if (argc == 1)
		return (nm("./a.out"));
	while (i < argc)
	{
		tmp = nm(argv[i]);
		res = res > tmp ? res : tmp;
		++i;
	}
	return (res);
}
