/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:11:30 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/26 10:31:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	mach_set_32(t_abstract_mach *header)
{
	if (!header)
		return ;
	if (header->file)
		header->header.arch_32 = header->file;
	header->header_size = sizeof(t_mach_header);
	header->nlist_size = sizeof(t_nlist);
	header->segment_size = sizeof(t_segment_command);
	header->section_size = sizeof(t_section);
}

void	mach_set_64(t_abstract_mach *header)
{
	if (!header)
		return ;
	if (header->file)
		header->header.arch_64 = header->file;
	header->header_size = sizeof(t_mach_header_64);
	header->nlist_size = sizeof(t_nlist_64);
	header->segment_size = sizeof(t_segment_command_64);
	header->section_size = sizeof(t_section_64);
}

t_abstract_mach	choose_type(const void *ptr, size_t size)
{
	uint32_t		magic_number;
	t_abstract_mach	header;

	header.file = NULL;
	if (!ptr)
		return (header);
	magic_number = *(int *)ptr;
	if (magic_number == FAT_CIGAM)
	{
		fat(ptr, size, 1);
		return (header);
	}
	else if (magic_number == FAT_MAGIC)
	{
		fat(ptr, size, 0);
		return (header);
	}
	header.big_endian = 0;
	header.file = ptr;
	header.file_size = size;
	header.eof = (uint64_t)ptr + size;
	if (magic_number == MH_MAGIC_64)
		mach_set_64(&header);
	else if (magic_number == MH_MAGIC)
		mach_set_32(&header);
	else if (magic_number == MH_CIGAM)
	{
		mach_set_32(&header);
		header.big_endian = 1;
	}
	parse(&header);
	return (header);
}
