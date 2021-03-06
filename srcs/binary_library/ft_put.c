/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:04:50 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 14:24:56 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <binary_loader.h>

void	ft_puthex(unsigned char c)
{
	static char hex_table[16] = "0123456789abcdef";

	ft_printf("%c", hex_table[c / 16]);
	ft_printf("%c", hex_table[c % 16]);
}
