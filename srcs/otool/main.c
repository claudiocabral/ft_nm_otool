/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:08:52 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 14:25:58 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <binary_loader.h>

int	otool_body(t_file file, int is_big_endian, const t_fat_arch *arch)
{
	t_abstract_mach	header;

	if (arch)
	{
		print_architecture(arch, is_big_endian, file.name, 0);
		file.ptr += endianless(is_big_endian, arch->offset);
		file.size = endianless(is_big_endian, arch->size);
	}
	else
		ft_printf("%s:\n", file.name);
	header = choose_type(file);
	if (!header.file.ptr)
		return (0);
	return (print_section(&header, "__text"));
}

int	otool(const char *filename)
{
	return (apply_to_file(filename, otool_body));
}

int	otool_error_no_file(void)
{
	write(STDERR_FILENO,
			"error: ft_otool: at least one file must be specified\n",
			sizeof("error: ft_otool: at least one file must be specified\n"));
	return (1);
}

int	main(int argc, char	**argv)
{
	int	i;
	int	tmp;
	int	res;

	i = 1;
	res = 0;
	if (argc == 1)
		return (otool_error_no_file());
	while (i < argc)
	{
		tmp = otool(argv[i]);
		res = res > tmp ? res : tmp;
		++i;
	}
	return (res);
}
