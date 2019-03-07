/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:28:06 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/07 10:11:42 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACH_TYPES_H
# define MACH_TYPES_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

typedef struct stat					t_stat;
typedef struct fat_header			t_fat_header;
typedef struct fat_arch				t_fat_arch;
typedef struct load_command			t_load_command;
typedef struct symtab_command		t_symtab_command;
typedef struct mach_header			t_mach_header;
typedef struct mach_header_64		t_mach_header_64;
typedef struct segment_command		t_segment_command;
typedef struct segment_command_64	t_segment_command_64;
typedef struct section				t_section;
typedef struct section_64			t_section_64;
typedef struct nlist				t_nlist;
typedef struct nlist_64				t_nlist_64;
typedef struct						s_file
{
	const uint8_t					*ptr;
	size_t							size;
	const char						*name;
}									t_file;
typedef struct						s_absctract_mach
{
	t_file							file;
	uint64_t						header_size;
	uint64_t						nlist_size;
	uint64_t						segment_size;
	uint64_t						section_size;
	uint64_t						eof;
	const char						*string_table;
	int								big_endian;
	int								number_of_sections;
	union							u_header
	{
		const t_mach_header			*arch_32;
		const t_mach_header_64		*arch_64;
	}								header;
	union							u_segment
	{
		t_segment_command			*arch_32;
		t_segment_command_64		*arch_64;
	}								segment;
	union							u_sections
	{
		t_section					**arch_32;
		t_section_64				**arch_64;
	}								sections;
	union							u_nlist
	{
		t_nlist						*arch_32;
		t_nlist_64					*arch_64;
	}								nlist;
}									t_abstract_mach;
typedef struct						s_range
{
	int	low;
	int	high;
}									t_range;
typedef struct						s_fat
{
	const t_fat_arch		*arch;
	const t_fat_header		*header;
	uint32_t				nbr_archs;
	int						is_big_endian;
	int						is_otool;
}									t_fat;

#endif
