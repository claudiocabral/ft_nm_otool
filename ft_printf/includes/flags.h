/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:18:06 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:18:09 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

char const	*hastag(char const *format, t_modifiers *modifiers);
char const	*zero(char const *format, t_modifiers *modifiers);
char const	*minus(char const *format, t_modifiers *modifiers);
char const	*plus(char const *format, t_modifiers *modifiers);
char const	*space(char const *format, t_modifiers *modifiers);

#endif
