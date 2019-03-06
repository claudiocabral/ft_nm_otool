/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:12:11 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/06 17:46:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

static void	collect_symbols(t_nlist_64 const **list,
						const t_nlist_64 *symbols,
						uint32_t number_of_symbols, uint64_t size)
{
	uint32_t	i;

	i = 0;
	while (i < number_of_symbols)
	{
		list[i] = (void *)symbols;
		symbols = (void *)symbols + size;
		++i;
	}
}

static void	sort(t_nlist_64 const **list, uint32_t number_of_symbols,
					t_abstract_mach *header)
{
	t_range	range;

	range.low = 0;
	range.high = number_of_symbols - 1;
	ft_quicksort((const void **)list, range, header, (t_cmpf)nlist_compare);
}

static void	print_symtab_command(const t_symtab_command *symbol_table,
				t_abstract_mach *header)
{
	const t_nlist_64	*symbols;
	t_nlist_64 const	**list;
	uint32_t			i;
	uint32_t			number_of_symbols;

	header->string_table = (const char *)header->file.ptr
		+ endianless(header->big_endian, symbol_table->stroff);
	symbols = (void *)(header->file.ptr
			+ endianless(header->big_endian, symbol_table->symoff));
	number_of_symbols = endianless(header->big_endian, symbol_table->nsyms);
	if ((size_t)header->string_table > header->eof
			|| (size_t)(symbols + number_of_symbols - 1) > header->eof)
		return ;
	if (!(list = (t_nlist_64 const **)malloc(sizeof(t_nlist_64 *)
					* number_of_symbols)))
		return ;
	collect_symbols(list, symbols, number_of_symbols, header->nlist_size);
	sort(list, number_of_symbols, header);
	i = 0;
	while (i < number_of_symbols)
	{
		print(list[i], header, header->string_table);
		++i;
	}
	free(list);
}

static int	loop_parse(uint32_t number_of_commands, const t_load_command *load,
				t_abstract_mach *header)
{
	uint32_t				i;

	i = 0;
	while (i < number_of_commands)
	{
		if (!is_in_file(load, sizeof(t_load_command), header->file))
			break ;
		if (load->cmd == endianless(header->big_endian, LC_SYMTAB))
		{
			print_symtab_command((const t_symtab_command *)load,
					header);
			break ;
		}
		load = (void *)load + endianless(header->big_endian, load->cmdsize);
		++i;
	}
	return (1);
}

int			parse(t_abstract_mach *header)
{
	const t_load_command	*load;
	uint64_t				number_of_commands;

	if (!header)
		return (0);
	load = (const t_load_command *)(header->file.ptr + header->header_size);
	if (header->header_size == sizeof(t_mach_header))
		number_of_commands =
			endianless(header->big_endian, header->header.arch_64->ncmds);
	else
		number_of_commands =
			endianless(header->big_endian, header->header.arch_32->ncmds);
	if (!(build_section_table(header, load, number_of_commands)))
		return (0);
	loop_parse(number_of_commands, load, header);
	free(header->sections.arch_64);
	return (1);
}
