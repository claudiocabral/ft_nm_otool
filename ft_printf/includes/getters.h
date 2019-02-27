/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:18:13 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:18:18 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTERS_H
# define GETTERS_H

# include <modifiers.h>
# include <wchar.h>

long				get_signed_int(t_modifiers *modifiers);
unsigned long		get_unsigned_int(t_modifiers *modifiers);
t_data				get_float_value(t_modifiers *moddifiers);
t_data				get_double(t_modifiers *modifiers);
t_data				get_character(t_modifiers *modifiers);
t_data				get_string(t_modifiers *modifiers);
t_data				get_pointer(t_modifiers *modifiers);
void				set_argument(t_modifiers *modifiers);
t_function			get_function(char c);

#endif
