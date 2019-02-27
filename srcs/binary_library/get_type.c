/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:47:57 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 11:39:21 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

char	get_symbol_from_section(const t_nlist_64 *list,
									t_abstract_mach *header)
{
	char	*name;

	if (header->section_size == sizeof(t_section_64))
		name = header->sections.arch_64[list->n_sect]->sectname;
	else
		name = header->sections.arch_32[list->n_sect]->sectname;
	if (ft_strcmp_s1_check(name, "__text", (const char *)header->eof) == 0)
		return ('T');
	else if (ft_strcmp_s1_check(name, "__data", (const char *)header->eof) == 0)
		return ('D');
	else if (ft_strcmp_s1_check(name, "__bss", (const char *)header->eof) == 0)
		return ('B');
	else
		return ('S');
}

char	get_type_symbol(const t_nlist_64 *list, t_abstract_mach *header)
{
	uint8_t	type;
	char	symbol;

	if (list->n_type & N_STAB)
		return ('-');
	type = list->n_type & N_TYPE;
	if (type == N_UNDF || type == N_PBUD)
		symbol = 'U';
	else if (type == N_ABS)
		symbol = 'A';
	else if (type == N_INDR)
		symbol = 'I';
	else if (type == N_SECT)
		symbol = get_symbol_from_section(list, header);
	else
		return (' ');

	if  (!(list->n_type & N_EXT))
		symbol += 32;
	return (symbol);
}
