/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 12:53:03 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 10:04:46 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <binary_loader.h>

int	map_file(char const *path, t_file *file)
{
	int		fd;
	t_stat	info;

	if (!file)
		return (0);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if (fstat(fd, &info) == -1)
	{
		close(fd);
		return (0);
	}
	if ((file->ptr = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
	{
		close(fd);
		return (0);
	}
	file->size = info.st_size;
	file->name = path;
	return (1);
}
