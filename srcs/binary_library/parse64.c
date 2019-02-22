/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:12:11 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/22 19:08:21 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	print(const t_nlist_64 *list, const char *string_table)
{
	char const	*type_table;
	char		type;

	type_table = "UTA3456789Ibudef";
	type = list->n_type & N_TYPE;
	// if (type == N_SECT)
		printf("%016llx %c %s\n", list->n_value,
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
}


void	print_symtab_command(const t_symtab_command *symbol_table,
		const char *ptr)
{
	const t_nlist_64	*list;
	const char			*string_table;
	uint32_t			i;

	string_table = ptr + symbol_table->stroff;
	list = (void *)(ptr + symbol_table->symoff);
	i = 0;
	while (i < symbol_table->nsyms)
	{
		print(list + i, string_table);
		++i;
	}
	(void)symbol_table;
}

const t_segment_command_64	*get_segment_command_64(t_load_command *load,
		uint32_t number_of_commands)
{
	uint32_t	i;

	i = 0;
	while (i < number_of_commands)
	{
		if (load->cmd == LC_SEGMENT)
		{
			return ((const t_segment_command_64 *)load);
		}
		load = (void *) load + load->cmdsize;
		++i;
	}
	return ((const t_segment_command_64 *)load);
}

void	parse64(const t_mach_header_64 *file)
{
	uint32_t					i;
	t_load_command				*load;
	const t_segment_command_64	*segment_table;

	if (!file)
		return ;
	load = (t_load_command*)(file + 1);
	segment_table = get_segment_command_64(load, file->ncmds);
	if (!segment_table)
		return ;
	i = 0;
	while (i < file->ncmds)
	{
		if (load->cmd == LC_SYMTAB)
		{
			print_symtab_command((const t_symtab_command *)load,
					(const char *)file);
			break ;
		}
		load = (void *) load + load->cmdsize;
		++i;
	}
}
