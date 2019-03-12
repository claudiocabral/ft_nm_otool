/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:20:30 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/12 11:24:16 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

int		check_table(const char *string_table, uint64_t offset, const char *eof)
{
	uint64_t	i;

	if ((string_table + offset >= eof))
		return (0);
	if (!string_table[offset])
		return (0);
	i = 0;
	string_table += offset;
	while (string_table + i < eof)
	{
		if (!string_table[i])
			return (1);
		++i;
	}
	return (0);
}

void	print32(const t_nlist *list, t_abstract_mach *header,
		const char *string_table)
{
	char		type;
	uint32_t	offset;

	type = list->n_type & N_TYPE;
	offset = endianless(header->big_endian, list->n_un.n_strx);
	type = get_type_symbol((t_nlist_64 *)list, header);
	if (type == '-')
		return ;
	if (type == 'U' && list->n_value)
		type = 'C';
	if (!check_table(string_table, offset, (const char *)header->eof))
		return ;
	if (type == 'U')
		ft_printf("         %c %s\n",
				type,
				string_table + offset);
	else
		ft_printf("%08x %c %s\n",
				endianless(header->big_endian, list->n_value),
				type,
				string_table + offset);
}

void	print64(const t_nlist_64 *list, t_abstract_mach *header,
		const char *string_table)
{
	char		type;
	uint64_t	offset;

	offset = endianless(header->big_endian, list->n_un.n_strx);
	type = get_type_symbol(list, header);
	if (type == '-')
		return ;
	else if (type == 'U' && list->n_value)
		type = 'C';
	if (!check_table(string_table, offset, (const char *)header->eof))
		return ;
	if (type == 'U')
		ft_printf("                 %c %s\n",
				type,
				string_table + list->n_un.n_strx);
	else
		ft_printf("%016llx %c %s\n",
				list->n_value,
				type,
				string_table + list->n_un.n_strx);
}

void	print(const t_nlist_64 *list, t_abstract_mach *header,
		const char *string_table)
{
	if (header->nlist_size == sizeof(t_nlist))
		print32((t_nlist *)list, header, string_table);
	else
		print64(list, header, string_table);
}
