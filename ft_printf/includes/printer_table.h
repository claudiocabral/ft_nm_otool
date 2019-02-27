/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:20:51 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:20:58 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_TABLE_H
# define PRINTER_TABLE_H

# include "print.h"
# include "modifiers.h"

static t_function	g_printers[19] =
{
	&print_invalid,
	&print_signed_decimal,
	&print_unsigned_decimal,
	&print_octal,
	&print_big_int_hex,
	&print_small_int_hex,
	&print_exp_big_float,
	&print_exp_small_float,
	&print_decimal_float,
	&print_var_big_float,
	&print_var_small_float,
	&print_big_float_hex,
	&print_small_float_hex,
	&print_char,
	&print_wide_char,
	&print_string,
	&print_wide_string,
	&print_pointer,
	&store_value,
};

#endif
