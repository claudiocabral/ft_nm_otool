/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 11:08:52 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/26 13:42:40 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <binary_loader.h>

int	otool(const char *filename)
{
	t_file	file;

	if (!(map_file(filename, &file)))
		return (1);
	choose_type(file.ptr, file.size, filename);
	munmap((void *)file.ptr, file.size);
	return (0);
}

int	otool_error_no_file(void)
{
	write(STDERR_FILENO,
			"error: ft_otool: at least one file must be specified",
			sizeof("error: ft_otool: at least one file must be specified"));
	return (1);
}

int	main(int argc, char	**argv)
{
	int	i;
	int	tmp;

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
