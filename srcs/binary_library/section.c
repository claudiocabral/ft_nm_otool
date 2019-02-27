/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:06:17 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 12:25:37 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int	print_section_32(t_abstract_mach *header, int i)
{
	t_section_64	*section;

	section = header->sections.arch_64[i];
	printf("Contents of (%s, %s) section\n", section->segname,
			section->sectname);
	return (1);
}

int	print_section_64(t_abstract_mach *header, int i)
{
	t_section_64	*section;

	section = header->sections.arch_64[i];
	printf("Contents of (%s, %s) section\n", section->segname,
			section->sectname);
	return (1);
}

int	print_section_contents(t_abstract_mach *header, int i)
{
	if (header->section_size == sizeof(t_section_64))
		return (print_section_64(header, i));
	return (print_section_32(header, i));
}

int	print_section(t_abstract_mach *header, const char *section_name)
{

	int						i;
	const t_load_command	*load;
	uint64_t				number_of_commands;

	load = (const t_load_command *)(header->file.ptr + header->header_size);
	if (header->header_size == sizeof(t_mach_header))
		number_of_commands =
			endianless(header->big_endian, header->header.arch_64->ncmds);
	else
		number_of_commands =
			endianless(header->big_endian, header->header.arch_32->ncmds);
	if (!build_section_table(header, load, number_of_commands))
		return (1);
	i = 1;
	while (i <= header->number_of_sections)
	{
		if (ft_strcmp_s1_check(header->sections.arch_64[i]->sectname,
					section_name, (const char *)header->eof) == 0)
		{
			print_section_contents(header, i);
			break ;
		}
	}
	return (0);
}
