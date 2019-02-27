/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:09:16 by ccabral           #+#    #+#             */
/*   Updated: 2019/02/27 11:47:25 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <binary_loader.h>

void	ft_swap(void const **a, void const **b)
{
	const void	*tmp;

	if (!a || !b)
		return ;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		nlist_compare(const t_nlist_64 *a, const t_nlist_64 *b,
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
				(const char *)header->eof
			);
	if (res == 0)
	{
		if (header->nlist_size == sizeof(t_nlist))
			return ((t_nlist *)a->n_value - (t_nlist *)b->n_value);
		return (a->n_value - b->n_value);

	}
	return (res);
}

int		ft_partition(void const **array, int low, int high,
		const void *data,t_cmpf cmpf)
{
	int			i;
	int			j;
	char const	*pivot;

	pivot = array[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (cmpf(array[j], (void *)pivot, data) < 0)
		{
			++i;
			ft_swap(array + i, array + j);
		}
		++j;
	}
	if (cmpf(array[high], array[i + 1], data) < 0)
		ft_swap(array + i + 1, array + high);
	return (i + 1);
}

void	ft_quicksort(void const **array, int low, int high,
		const void *data, t_cmpf cmpf)
{
	int	p;

	if (low < high)
	{
		p = ft_partition(array, low, high, data, cmpf);
		ft_quicksort(array, low, p - 1, data, cmpf);
		ft_quicksort(array, p + 1, high, data, cmpf);
	}
}
