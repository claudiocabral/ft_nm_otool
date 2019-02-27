/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:16:46 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:16:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

# include <modifiers.h>

int	is_signed_int(t_type type);
int	is_unsigned_int(t_type type);
int	is_float(t_type type);
int	is_character(t_type type);
int	is_string(t_type type);

int	is_int_type(char c);
int	is_float_type(char c);
int	is_char_type(char c);
int	is_string_type(char c);

int	is_digit(char c);
int	is_flag(char c);
int	is_length_modifier(char c);
int	is_conversion(char c);

#endif
