/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:12:11 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 20:02:55 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	print_symtab_command(const t_symtab_command *symbol_table,
				t_abstract_mach *header, uint32_t text_section)
{
	const t_nlist_64	*symbols;
	t_nlist_64 const	**list;
	uint32_t			i;
	uint32_t			number_of_symbols;

	header->string_table = header->file
		+ endianless(header->big_endian, symbol_table->stroff);
	symbols = (void *)(header->file
			+ endianless(header->big_endian, symbol_table->symoff));
	number_of_symbols = endianless(header->big_endian, symbol_table->nsyms);
	if ((size_t)header->string_table > header->eof
			|| (size_t)(symbols + number_of_symbols - 1) > header->eof)
		return ;
	if (!(list = (t_nlist_64 const **)malloc(sizeof(t_nlist_64 *)
					* number_of_symbols)))
		return;
	i = 0;
	while (i < number_of_symbols)
	{
		list[i] = (void *)symbols;
		symbols = (void *)symbols + header->nlist_size;
		++i;
	}
	ft_quicksort((const void **)list, 1,
			number_of_symbols - 1, header, (t_cmpf)nlist_compare);
	i = 0;
	while (i < number_of_symbols)
	{
		print(list[i], header, header->string_table, text_section);
		++i;
	}
	free(list);
}

void	parse(t_abstract_mach *header)
{
	uint32_t				i;
	const t_load_command	*load;
	uint32_t				text_section;
	uint64_t				number_of_commands;

	(void)text_section;
	if (!header)
		return ;
	load = header->file + header->header_size;
	if (header->header_size == sizeof(t_mach_header))
		number_of_commands =
			endianless(header->big_endian, header->header.arch_64->ncmds);
	else
		number_of_commands =
			endianless(header->big_endian, header->header.arch_32->ncmds);
	//text_section = get_text_section((void *)load, number_of_commands, header->eof);
	i = 0;
	while (i < number_of_commands)
	{
		if (load->cmd == endianless(header->big_endian, LC_SYMTAB))
		{
			print_symtab_command((const t_symtab_command *)load,
					header, 0);
			break ;
		}
		load = (void *) load + endianless(header->big_endian, load->cmdsize);
		if (!is_in_file(load, sizeof(t_load_command), header->file,
												header->file_size))
			break ;
		++i;
	}
}
