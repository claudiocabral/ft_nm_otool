/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 18:06:29 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:43:33 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

char	*ftprintf_itoa_base(unsigned long value, char const *base)
{
	char	tmp[128];
	int		base_size;
	int		i;

	tmp[127] = 0;
	base_size = ftprintf_strlen(base);
	i = 126;
	while (1)
	{
		tmp[i] = base[value % base_size];
		value /= base_size;
		--i;
		if (!value)
			break ;
	}
	return (ftprintf_strdup(tmp + i + 1));
}
