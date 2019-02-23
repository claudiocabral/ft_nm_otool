/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_loader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:41:29 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 19:33:42 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_LOADER_H
# define BINARY_LOADER_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <mach_types.h>

typedef int		(*t_cmpf) (void const *, void const *, void const *);

typedef struct	s_absctract_mach
{
	uint64_t	file_size;
	uint64_t	header_size;
	uint64_t	nlist_size;
	uint64_t	segment_size;
	uint64_t	section_size;
	uint64_t	eof;
	const void	*file;
	const char	*string_table;
	int			big_endian;
	union
	{
		const t_mach_header		*arch_32;
		const t_mach_header_64	*arch_64;
	}			header;
	union
	{
		t_segment_command		*arch_32;
		t_segment_command_64	*arch_64;
	}			segment;
	union
	{
		t_section		*arch_32;
		t_section_64	*arch_64;
	}			section;
	union
	{
		t_nlist		*arch_32;
		t_nlist_64	*arch_64;
	}			nlist;
}				t_abstract_mach;

typedef struct	s_file
{
	const uint8_t	*ptr;
	size_t			size;
}				t_file;

void			fat(const void *file, size_t size);
int				map_file(char const *path, t_file *file);
void			parse(t_abstract_mach *header);
void			choose_type(const void *ptr, size_t size);
void			ft_quicksort(void const **array, int low, int high,
									const void *data, t_cmpf cmpf);
int				ft_strcmp(const char *s1, const char *s2);
void			print(const t_nlist_64 *list, t_abstract_mach *header,
						const char *string_table, uint32_t text_section);
uint32_t		get_text_section(t_segment_command_64 *load,
						uint32_t number_of_commands, size_t max);
int				nlist_compare(const t_nlist_64 *a, const t_nlist_64 *b,
											t_abstract_mach *header);
uint32_t		big_to_little_endian(uint32_t val);
uint32_t		endianless(int is_endian, uint32_t val);

#endif
