/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:00:57 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 18:54:33 by ccabral          ###   ########.fr       */
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

uint32_t	get_text_section(t_segment_command_64 *load,
				uint32_t number_of_commands, size_t max)
{
	(void)max;

	uint32_t					i;
	uint32_t					total;
	const t_segment_command_64	*segment;

	i = 0;
	total = 0;
	while (i < number_of_commands)
	{
		if (load->cmd == LC_SEGMENT_64 || LC_SEGMENT)
		{
			segment = (void *)load;
			printf("%s %llu\n", segment->segname, segment->fileoff);
			print_segment(segment);
					
		}
		load = (void *) load + load->cmdsize;
		if ((size_t)load > max - (sizeof(t_load_command)))
			break ;
		++i;
	}
	return (0);
}
