/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:00:57 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 15:36:50 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

uint32_t	print_segment(const t_segment_command_64 *segment)
{
	const t_section_64	*section;
	uint32_t			i;

	i = 0;
	section = (const void *)segment + sizeof(t_segment_command_64);
	while (i < segment->nsects)
	{
		ft_printf("[%u]: %s\n", i, section->sectname);
		++i;
		section = (void *)section + section->size;
	}
	return (0);
}

uint32_t	get_number_of_sections(const t_load_command *load,
				uint32_t number_of_commands, t_abstract_mach *header)
{
	uint32_t					i;
	uint32_t					total;
	uint32_t					cmd;

	i = 0;
	total = 0;
	while (i < number_of_commands)
	{
		if (!is_in_file(load, sizeof(t_load_command),
					header->file)
				|| !is_in_file(load, endianless(header->big_endian,
						load->cmdsize), header->file))
			return (total);
		cmd = endianless(header->big_endian, load->cmd);
		if (cmd == LC_SEGMENT_64)
			total += endianless(header->big_endian,
					((t_segment_command_64 *)load)->nsects);
		else if (cmd == LC_SEGMENT)
			total += endianless(header->big_endian,
					((t_segment_command *)load)->nsects);
		load = (void *)load + endianless(header->big_endian, load->cmdsize);
		++i;
	}
	return (total);
}

void		collect_sections(uint32_t *section_index, const t_load_command *cmd,
								t_abstract_mach *header, uint32_t total_sects)
{
	uint32_t					i;
	uint32_t					n_sects;

	i = 0;
	if (header->segment_size == sizeof(t_segment_command_64))
		n_sects = endianless(header->big_endian,
				((t_segment_command_64 *)cmd)->nsects);
	else
		n_sects = endianless(header->big_endian,
				((t_segment_command *)cmd)->nsects);
	cmd = (const void *)cmd + header->segment_size;
	while (i < n_sects)
	{
		if (*section_index > total_sects)
			return ;
		if (!is_in_file(cmd, header->section_size,
					header->file))
			return ;
		header->sections.arch_64[*section_index] = (t_section_64 *)cmd;
		*section_index += 1;
		++i;
		cmd = (const void *)cmd + header->section_size;
	}
}

int			build_section_table(t_abstract_mach *header,
				const t_load_command *load, uint32_t number_of_commands)
{
	uint32_t					i;
	uint32_t					section_index;
	uint32_t					cmd;

	if (!(header->number_of_sections =
				get_number_of_sections(load, number_of_commands, header))
		|| !(header->sections.arch_64 =
			(t_section_64 **)malloc((header->number_of_sections + 1)
					* sizeof(t_section_64 *))))
		return (0);
	i = 0;
	section_index = 1;
	while (i++ < number_of_commands)
	{
		if (!is_in_file(load, sizeof(t_load_command), header->file)
				|| !is_in_file(load, endianless(header->big_endian,
						load->cmdsize), header->file))
			return (1);
		cmd = endianless(header->big_endian, load->cmd);
		if (cmd == LC_SEGMENT_64 || cmd == LC_SEGMENT)
			collect_sections(&section_index, load, header,
					header->number_of_sections);
		load = (void *)load + endianless(header->big_endian, load->cmdsize);
	}
	return (1);
}
