/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:11:30 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 11:30:07 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	mach_set_32(t_abstract_mach *header)
{
	if (!header)
		return ;
	if (header->file.ptr)
		header->header.arch_32 = (const t_mach_header *)header->file.ptr;
	header->header_size = sizeof(t_mach_header);
	header->nlist_size = sizeof(t_nlist);
	header->segment_size = sizeof(t_segment_command);
	header->section_size = sizeof(t_section);
}

void	mach_set_64(t_abstract_mach *header)
{
	if (!header)
		return ;
	if (header->file.ptr)
		header->header.arch_64 = (const t_mach_header_64 *)header->file.ptr;
	header->header_size = sizeof(t_mach_header_64);
	header->nlist_size = sizeof(t_nlist_64);
	header->segment_size = sizeof(t_segment_command_64);
	header->section_size = sizeof(t_section_64);
}

t_abstract_mach	choose_type(t_file file)
{
	uint32_t		magic_number;
	t_abstract_mach	header;

	magic_number = *(int *)file.ptr;
	header.file.ptr = NULL;
	if (!file.ptr)
		return (header);
	header.big_endian = 0;
	header.file.ptr = file.ptr;
	header.file.size = file.size;
	header.eof = (uint64_t)file.ptr + file.size;
	if (magic_number == MH_MAGIC_64)
		mach_set_64(&header);
	else if (magic_number == MH_MAGIC)
		mach_set_32(&header);
	else if (magic_number == MH_CIGAM)
	{
		mach_set_32(&header);
		header.big_endian = 1;
	}
	else
		header.file.ptr = NULL;
	if (!is_in_file(header.file.ptr, header.header_size, file))
		header.file.ptr = NULL;
	return (header);
}
