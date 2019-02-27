/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:23:36 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 13:23:37 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <conversion_table.h>

t_function	get_function(char index)
{
	if (index < 0)
		return (g_functions[0]);
	return (g_functions[(unsigned char)index]);
}
