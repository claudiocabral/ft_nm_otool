/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:12:11 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 14:37:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	print64(const t_nlist_64 *list, const char *string_table)
{
	char const	*type_table;
	char		type;

	type_table = "UTA3T56789IbudTf";
	type = list->n_type & N_TYPE;
	if (!string_table[list->n_un.n_strx])
		return ;
	if (type == N_UNDF)
		printf("                 %c %s\n",
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
	else if (type == N_UNDF)
		printf("%016llx %c %s\n",
				list->n_value,
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
	else
		printf("%016llx %c %s\n",
				list->n_value,
				type_table[list->n_type & N_TYPE],
				string_table + list->n_un.n_strx);
}


void	print_symtab_command(const t_symtab_command *symbol_table,
		const char *ptr, size_t max)
{
	const t_nlist_64	*symbols;
	t_nlist_64 const	**list;
	const char			*string_table;
	uint32_t			i;

	string_table = ptr + symbol_table->stroff;
	symbols = (void *)(ptr + symbol_table->symoff);
	if ((size_t)string_table > max
			|| (size_t)(symbols + symbol_table->nsyms - 1) > max)
		return ;
	if (!(list = (t_nlist_64 const **)malloc(sizeof(t_nlist_64 *)
					* symbol_table->nsyms)))
		return;
	i = 0;
	while (i < symbol_table->nsyms)
	{
		list[i] = symbols + i;
		++i;
	}
	ft_quicksort((const void **)list, 1,
			symbol_table->nsyms - 1, string_table, (t_cmpf)nlist_64_compare);
	i = 0;
	while (i < symbol_table->nsyms)
	{
		print64(list[i], string_table);
		++i;
	}
	(void)symbol_table;
}

const t_segment_command_64	*get_segment_command_64(t_load_command *load,
		uint32_t number_of_commands, size_t max)
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
		if ((size_t)load > max - (sizeof(t_load_command)))
			break ;
		++i;
	}
	return ((const t_segment_command_64 *)load);
}

void	parse64(const t_mach_header_64 *file, size_t max)
{
	uint32_t					i;
	t_load_command				*load;
	const t_segment_command_64	*segment_table;

	if (!file)
		return ;
	load = (t_load_command*)(file + 1);
	segment_table = get_segment_command_64(load, file->ncmds, max);
	if (!segment_table)
		return ;
	i = 0;
	while (i < file->ncmds)
	{
		if (load->cmd == LC_SYMTAB)
		{
			print_symtab_command((const t_symtab_command *)load,
					(const char *)file, max);
			break ;
		}
		load = (void *) load + load->cmdsize;
		if ((size_t)load > max - (sizeof(t_load_command)))
			break ;
		++i;
	}
}
