/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:29:28 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/14 16:18:35 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stdlib.h>
#include <wchar.h>

long	ftprintf_max(long a, long b)
{
	return ((a > b) ? a : b);
}

long	ftprintf_min(long a, long b)
{
	return ((a < b) ? a : b);
}

size_t	ftprintf_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

char	*ftprintf_strdup(char const *src)
{
	const char	*head;
	char		*dup;
	int			size;

	head = src;
	size = 1;
	while (*src)
	{
		++size;
		++src;
	}
	if ((dup = (char *)malloc(sizeof(char) * size)) == 0)
		return (NULL);
	src = head;
	head = dup;
	while (*src)
		*dup++ = *src++;
	*dup = '\0';
	return ((char *)head);
}
