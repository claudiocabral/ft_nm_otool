/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_loader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:41:29 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/22 18:59:46 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_LOADER_H
# define BINARY_LOADER_H

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct stat t_stat;
typedef struct mach_header_64 t_mach_header_64;
typedef struct load_command t_load_command;
typedef struct symtab_command t_symtab_command;
typedef struct segment_command_64 t_segment_command_64;
typedef struct nlist_64 t_nlist_64;

typedef struct	s_file
{
	const uint8_t	*ptr;
	size_t			size;
}					t_file;

int		map_file(char const *path, t_file *file);
void	parse32(const void *file);
void	parse64(const t_mach_header_64 *file);
void	choose_type(const void *ptr);

#endif
