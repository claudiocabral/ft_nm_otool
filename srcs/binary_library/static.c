/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:40:53 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/05 15:51:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mach-o/ranlib.h>
#include <binary_loader.h>

int	handle_static_library(t_file file)
{
}

int	parse_static_library(t_file file)
{
	if (file.size < 68)
		return (0);
	if (ft_strncmp((const char *)file.ptr, "!<arch>\n", 8) == 0)
		return (handle_static_library(file));
	return (0);
}
