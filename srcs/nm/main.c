/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:07:21 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/26 13:35:17 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>
#include <sys/mman.h>
#include <unistd.h>

int	nm(const char *filename)
{
	t_file	file;

	if (!(map_file(filename, &file)))
		return (1);
	choose_type(file.ptr, file.size, filename);
	munmap((void *)file.ptr, file.size);
	return (0);
}

int	nm_error_no_file(void)
{
	write(STDERR_FILENO,
			"error: ft_nm: at least one file must be specified\n",
			50);
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
		return (nm("./a.out"));
	while (i < argc)
	{
		tmp = nm(argv[i]);
		res = res > tmp ? res : tmp;
		++i;
	}
	return (res);
}
