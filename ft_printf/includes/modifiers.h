/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:19:35 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/11 16:55:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODIFIERS_H
# define MODIFIERS_H

# include <stdarg.h>
# include <wchar.h>

typedef union		u_data
{
	char				c;
	wchar_t				wc;
	char				*s;
	wchar_t				*ws;
	long long			ll;
	unsigned long long	ull;
	long double			f;
}					t_data;

typedef enum		e_type
{
	NULL_T = 0,
	SIGNED_DECIMAL = 1,
	UNSIGNED_DECIMAL = 2,
	OCTAL = 3,
	BIG_HEX = 4,
	SMALL_HEX = 5,
	EXPONENTIAL_BIG_DOUBLE = 6,
	EXPONENTIAL_SMALL_DOUBLE = 7,
	DECIMAL_DOUBLE = 8,
	VARIABLE_STYLE_BIG_DOUBLE = 9,
	VARIABLE_STYLE_SMALL_DOUBLE = 10,
	DOUBLE_BIG_HEX = 11,
	DOUBLE_SMALL_HEX = 12,
	CHAR = 13,
	WIDE_CHAR = 14,
	STRING = 15,
	WIDE_STRING = 16,
	POINTER = 17,
	STORAGE = 18
}					t_type;

typedef enum		e_flag
{
	NO_FLAGS = 0,
	HASHTAG = 0x1,
	ZERO = 0x2,
	MINUS = 0x4,
	PLUS = 0x8,
	SPACE = 0x10,
	APOSTROPHE = 0x20
}					t_flag;

typedef enum		e_length_modfier
{
	NONE = 0,
	HH = 1,
	H = 2,
	L = 3,
	LL = 4,
	J = 5,
	T = 6,
	Z = 7,
	BIG_L = 8
}					t_length_modifier;

typedef struct		s_modifiers
{
	t_type				type;
	t_flag				flags;
	int					field_width;
	int					precision;
	int					arg_number;
	t_length_modifier	length;
	int					total_size;
	char				*separator;
	int					separator_size;
	va_list				args;
	int					fd;
}					t_modifiers;

typedef char const	*(*t_function)(char const *, t_modifiers *);

void				init_modifiers(t_modifiers *modifiers, int fd,
													va_list *args);
void				clean_modifiers(t_modifiers *modifiers);
void				reset_modifiers(t_modifiers *modifiers);

#endif
