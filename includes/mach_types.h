/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:28:06 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 19:02:49 by ccabral          ###   ########.fr       */
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

#endif
