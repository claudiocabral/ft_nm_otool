/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makers.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:18:28 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:18:38 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKERS_H
# define MAKERS_H

# include <modifiers.h>

char	*make_hex_string(unsigned long long value, char const *const hex_set,
														t_modifiers *modifiers);
char	*make_octal_string(unsigned long long value, t_modifiers *modifiers);
char	*make_decimal_string(unsigned long long value, int sign,
														t_modifiers *modifiers);
#endif
