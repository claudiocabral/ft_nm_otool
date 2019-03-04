/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:09:16 by ccabral           #+#    #+#             */
/*   Updated: 2019/03/04 16:10:07 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void		ft_swap(void const **a, void const **b)
{
	const void	*tmp;

	if (!a || !b)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int			nlist_compare(const t_nlist_64 *a, const t_nlist_64 *b,
		t_abstract_mach *header)
{
	uint32_t	a_offset;
	uint32_t	b_offset;
	int			res;

	a_offset = endianless(header->big_endian, a->n_un.n_strx);
	b_offset = endianless(header->big_endian, b->n_un.n_strx);
	res = ft_strcmp_safe(
				header->string_table + a_offset,
				header->string_table + b_offset,
				(const char *)header->eof);
	if (header->nlist_size == sizeof(t_nlist))
	{
		a_offset = endianless(header->big_endian, ((t_nlist *)a)->n_un.n_strx);
		b_offset = endianless(header->big_endian, ((t_nlist *)b)->n_un.n_strx);
	}
	else
	{
		a_offset = endianless(header->big_endian, a->n_value);
		b_offset = endianless(header->big_endian, b->n_value);
	}
	if (res == 0)
		return (a_offset - b_offset);
	return (res);
}

static int	ft_partition(void const **array, t_range range,
		const void *data, t_cmpf cmpf)
{
	int			i;
	int			j;
	char const	*pivot;

	pivot = array[range.high];
	i = range.low - 1;
	j = range.low;
	while (j < range.high)
	{
		if (cmpf(array[j], (void *)pivot, data) < 0)
		{
			++i;
			ft_swap(array + i, array + j);
		}
		++j;
	}
	if (cmpf(array[range.high], array[i + 1], data) < 0)
		ft_swap(array + i + 1, array + range.high);
	return (i + 1);
}

void		ft_quicksort(void const **array, t_range range,
		const void *data, t_cmpf cmpf)
{
	int		p;
	t_range small;
	t_range big;

	if (range.low < range.high)
	{
		p = ft_partition(array, range, data, cmpf);
		small.low = range.low;
		small.high = p - 1;
		big.low = p + 1;
		big.high = range.high;
		ft_quicksort(array, small, data, cmpf);
		ft_quicksort(array, big, data, cmpf);
	}
}
