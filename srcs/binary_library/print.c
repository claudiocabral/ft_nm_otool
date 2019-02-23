/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:20:30 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 19:47:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	print32(const t_nlist *list, t_abstract_mach *header,
		const char *string_table, uint32_t text_section)
{
	char const	*type_table;
	char		type;
	uint32_t	type_value;
	uint32_t	offset;

	type_table = "UTA3T56789IbudTf";
	type = list->n_type & N_TYPE;
	offset = endianless(header->big_endian, list->n_un.n_strx);
	type_value = endianless(header->big_endian, list->n_type);
	text_section = list->n_sect;
	if ((uint64_t)string_table + offset >= header->eof)
		return ;
	if (!string_table[offset])
		return ;
	if (type == N_UNDF)
		printf("         %c %s\n",
				type_table[type_value & N_TYPE],
				string_table + offset);
	else if (type != N_SECT)
		printf("%08x %c %s\n",
				endianless(header->big_endian, list->n_value),
				type_table[type_value & N_TYPE],
				string_table + offset);
	else if(list->n_sect == text_section)
		printf("%08x %c %s\n",
				endianless(header->big_endian, list->n_value),
				type_table[type_value & N_TYPE],
				string_table + offset);
}

void	print64(const t_nlist_64 *list, t_abstract_mach *header,
		const char *string_table, uint32_t text_section)
{
	char const	*type_table;
	char		type;

	type_table = "UTA3T56789IbudTf";
	type = list->n_type & N_TYPE;
	text_section = list->n_sect;
	if ((uint64_t)string_table + list->n_un.n_strx >= header->eof)
		return ;
	if (!string_table[list->n_un.n_strx])
		return ;
	if (type == N_UNDF)
		printf("                 %c %s\n",
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
	else if (type != N_SECT)
		printf("%016llx %c %s\n",
				list->n_value,
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
	else if(list->n_sect == text_section)
		printf("%016llx %c %s\n",
				list->n_value,
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
}

void	print(const t_nlist_64 *list, t_abstract_mach *header,
		const char *string_table, uint32_t text_section)
{

	if (header->nlist_size == sizeof(t_nlist))
		print32((t_nlist *)list, header, string_table, text_section);
	else
		print64(list, header, string_table, text_section);
}
