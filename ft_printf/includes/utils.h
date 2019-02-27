/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:20:54 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/14 16:14:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <wchar.h>

long				ftprintf_max(long a, long b);
long				ftprintf_min(long a, long b);
size_t				ftprintf_strlen(char const *str);
char				*ftprintf_strdup(char const *src);
char				*ftprintf_itoa_base(unsigned long value, char const *base);

#endif
