/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:06:17 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 15:54:58 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int	print_section_32(t_abstract_mach *header, int i)
{
	t_section	*section;

	section = header->sections.arch_32[i];
	ft_printf("Contents of (%s,%s) section\n", section->segname,
			section->sectname);
	if (header->big_endian)
		hexdump_32_packed((const char *)header->file.ptr
				+ endianless(header->big_endian, section->offset),
				endianless(header->big_endian, section->size),
				endianless(header->big_endian, section->addr));
	else
		hexdump_32((const char *)header->file.ptr
				+ endianless(header->big_endian, section->offset),
				endianless(header->big_endian, section->size),
				endianless(header->big_endian, section->addr));
	return (1);
}

int	print_section_64(t_abstract_mach *header, int i)
{
	t_section_64	*section;

	section = header->sections.arch_64[i];
	ft_printf("Contents of (%s,%s) section\n", section->segname,
			section->sectname);
	if (!is_in_file(header->file.ptr + section->offset,
				section->size, header->file))
		return (0);
	hexdump((const char *)header->file.ptr + section->offset, section->size,
			section->addr);
	return (1);
}

int	print_section_contents(t_abstract_mach *header, int i)
{
	if (header->section_size == sizeof(t_section_64))
		return (print_section_64(header, i));
	return (print_section_32(header, i));
}

int	loop_print_section(t_abstract_mach *header, const char *section_name)
{
	int	i;

	i = 1;
	while (i <= header->number_of_sections)
	{
		if (ft_strcmp_s1_check(header->sections.arch_64[i]->sectname,
					section_name, (const char *)header->eof) == 0)
		{
			return (print_section_contents(header, i));
			break ;
		}
		++i;
	}
	return (0);
}

int	print_section(t_abstract_mach *header, const char *section_name)
{
	const t_load_command	*load;
	uint64_t				number_of_commands;
	int						res;

	load = (const t_load_command *)(header->file.ptr + header->header_size);
	if (header->header_size == sizeof(t_mach_header))
		number_of_commands =
			endianless(header->big_endian, header->header.arch_64->ncmds);
	else
		number_of_commands =
			endianless(header->big_endian, header->header.arch_32->ncmds);
	if (!build_section_table(header, load, number_of_commands))
		return (0);
	res = loop_print_section(header, section_name);
	free(header->sections.arch_64);
	return (res);
}
