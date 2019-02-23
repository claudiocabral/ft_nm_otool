/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:00:57 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 20:13:19 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

uint32_t	print_segment(const t_segment_command_64 *segment)
{
	const struct section_64	*section;
	uint32_t			i;

	i = 0;
	section = (const void *)segment + sizeof(t_segment_command_64);
	while (i < segment->nsects)
	{
		printf("[%u]: %s\n", i, section->sectname);
		++i;
		section = (void *)section + section->size;
	}
	return (0);
}
uint32_t	get_number_of_sections(t_load_command *load,
				uint32_t number_of_commands, t_abstract_mach *header)
{
	uint32_t					i;
	uint32_t					total;

	i = 0;
	total = 0;
	while (i < number_of_commands)
	{
		if (load->cmd == LC_SEGMENT_64)
		{
			print_segment((t_segment_command_64 *)load);
		}
		load = (void *) load + load->cmdsize;
		if (!is_in_file(load, sizeof(t_load_command),
					header->file, header->file_size))
			break ;
		++i;
	}
	return (0);
}

uint32_t	get_text_section(t_load_command *load,
				uint32_t number_of_commands, t_abstract_mach *header)
{
	uint32_t					i;
	uint32_t					total;

	i = 0;
	total = 0;
	while (i < number_of_commands)
	{
		if (endianless(header->big_endian, load->cmd) == LC_SEGMENT_64)
		{
			print_segment((t_segment_command_64 *)load);
		}
		load = (void *) load + endianless(header->big_endian, load->cmdsize);
		if (!is_in_file(load, sizeof(t_load_command),
					header->file, header->file_size))
			break ;
		++i;
	}
	return (0);
}
