/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:12:25 by conobi            #+#    #+#             */
/*   Updated: 2021/12/13 20:00:28 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	heapify(int **arr, int n, int i)
{
	int	largest;
	int	l;
	int	r;

	largest = i;
	l = 2 * i + 1;
	r = 2 * i + 2;
	if (l < n && *arr[largest] < *arr[l])
		largest = l;
	if (r < n && *arr[largest] < *arr[r])
		largest = r;
	if (largest != i)
	{
		ft_swap(arr[i], arr[largest]);
		heapify(arr, i, 0);
	}
}

void	heap_sort(int **arr, int n)
{
	int	i;

	i = 0;
	while ((i <= n / 2 - 1) && i != -1)
	{
		heapify(arr, n, i);
		i--;
	}
	while ((i <= n - 1) && i != 0)
	{
		ft_swap(arr[i], arr[0]);
		heapify(arr, n, 0);
		i--;
	}
}
