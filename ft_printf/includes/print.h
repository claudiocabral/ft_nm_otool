/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:27:28 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/02 22:00:57 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <string.h>
# include <modifiers.h>

typedef t_data		(*t_getter)(t_modifiers *);
typedef char		*(*t_generate_string)(t_data, t_modifiers *);
typedef void		(*t_print)(char const *, t_modifiers *);

char				get_number_sign(long value, t_modifiers *modifiers);
t_function			get_printer(int index);
void				generic_print(t_modifiers *modifiers, t_getter get_value,
												t_generate_string generator,
												t_print	print);
void				print_with_padding(char const *str,
										t_modifiers *modifiers, int nbr_chars);
void				print_padding(int size, int use_zero, int fd);
char const			*print_formated(char const *str, t_modifiers *modifiers);
void				increase_count(unsigned int size);
unsigned long long	write_and_count(int fd, char const *str, size_t size);
unsigned long long	get_character_count(void);
void				reset_character_count(void);
void				decrement_count(int i);
char const			*no_op(char const *format, t_modifiers *modifiers);
char const			*print_invalid(char const *format, t_modifiers *modifiers);
char const			*print_signed_decimal(char const *format,
											t_modifiers *modifiers);
char const			*print_unsigned_decimal(char const *format,
											t_modifiers *modifiers);
char const			*print_octal(char const *format,
											t_modifiers *modifiers);
char const			*print_big_int_hex(char const *format,
											t_modifiers *modifiers);
char const			*print_small_int_hex(char const *format,
											t_modifiers *modifiers);
char const			*print_exp_big_float(char const *format,
											t_modifiers *modifiers);
char const			*print_exp_small_float(char const *format,
											t_modifiers *modifiers);
char const			*print_decimal_float(char const *format,
											t_modifiers *modifiers);
char const			*print_var_big_float(char const *format,
											t_modifiers *modifiers);
char const			*print_var_small_float(char const *format,
											t_modifiers *modifiers);
char const			*print_big_float_hex(char const *format,
											t_modifiers *modifiers);
char const			*print_small_float_hex(char const *format,
											t_modifiers *modifiers);
char const			*print_char(char const *format, t_modifiers *modifiers);
char const			*print_wide_char(char const *format,
											t_modifiers *modifiers);
char const			*print_string(char const *format, t_modifiers *modifiers);
char const			*print_wide_string(char const *format,
											t_modifiers *modifiers);
char const			*print_pointer(char const *format, t_modifiers *modifiers);
char const			*store_value(char const *format, t_modifiers *modifiers);
int					wide_char_to_string(wchar_t value, char *str);
void				print_string_helper(char const *str,
													t_modifiers *modifiers);

#endif
