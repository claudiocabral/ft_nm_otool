/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:11:30 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/23 14:05:51 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	choose_type(const void *ptr, size_t size)
{
	uint32_t	magic_number;

	if (!ptr)
		return ;
	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
		parse64(ptr, (size_t)ptr + size);
	else if (magic_number == MH_MAGIC)
		parse32(ptr);
}
