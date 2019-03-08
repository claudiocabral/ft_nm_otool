/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_loader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:41:29 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/08 12:54:54 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_LOADER_H
# define BINARY_LOADER_H

# include <stdint.h>
# include <stdlib.h>
# include <mach_types.h>
# include <ft_printf.h>

# define NOT_FAT -1
# define HEADER 8

typedef int		(*t_cmpf)(void const *, void const *, void const *);
typedef int		(*t_func)(t_file file, int is_big_endian,
									const t_fat_arch *arch, int is_static_lib);
int				fat_handler(t_file file, int is_big_endian,
									int is_otool, t_func f);
int				map_file(char const *path, t_file *file);
int				parse(t_abstract_mach *header);
t_abstract_mach	choose_type(t_file file);
void			ft_quicksort(void const **array, t_range range,
									const void *data, t_cmpf cmpf);
void			print(const t_nlist_64 *list, t_abstract_mach *header,
						const char *string_table);
int				ft_isdigit(int c);
uint32_t		get_text_section(t_load_command *load,
					uint32_t number_of_commands, t_abstract_mach *header);
int				nlist_compare(const t_nlist_64 *a, const t_nlist_64 *b,
											t_abstract_mach *header);
uint32_t		big_to_little_endian(uint32_t val);
uint32_t		endianless(int is_endian, uint32_t val);
int				is_in_file(const void *ptr, size_t size, t_file file);
int				build_section_table(t_abstract_mach *header,
					const t_load_command *load, uint32_t number_of_commands);
char			get_type_symbol(const t_nlist_64 *list,
									t_abstract_mach *header);
int				fat_endianless(t_file file, int is_otool, t_func f);
int				apply_to_file(const char *filename, t_func f,
									int multiple, int is_otools);
void			print_architecture(const t_fat_arch *arch, int is_big_endian,
										const char *filename, int skip_line);
int				ft_strncmp(const char *s1, const char *s2, size_t size);
int32_t			ft_natoi(const char *val, size_t size);
int				ft_strcmp_safe(const char *s1, const char *s2,
												const char *eof);
int				ft_strcmp_s1_check(const char *s1, const char *s2,
													const char *eof);
int				print_section(t_abstract_mach *header,
								const char *section_name);
void			ft_puthex(unsigned char c);
int				hexdump(const char *buffer, uint64_t size, uint64_t address);
int				hexdump_32(const char *buffer, uint32_t size,
											uint32_t address);
int				hexdump_32_packed(const char *buffer, uint32_t size,
											uint32_t address);
int				parse_static_library(t_file file, t_func f, int is_otools);
int				try_native(t_fat *fat, t_file file, t_func f);
int				single_architecture(t_file file, const t_fat_arch *arch,
									int is_big_endian, t_func f);
int				apply_to_architecture(t_fat *fat, t_file file,
											int index, t_func f);
#endif
