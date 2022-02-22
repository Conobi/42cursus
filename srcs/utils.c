/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:12 by conobi            #+#    #+#             */
/*   Updated: 2022/02/22 17:55:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	f_atoi(char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	while (str[i] && '0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + str[i] - '0';
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return (nbr);
}

double	calc_ts(double start_date)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) - start_date);
}

void	printer(int ts, int id, short action, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%d %d ", ts, id);
	if (action == 0)
		printf("has taken a fork\n");
	else if (action == 1)
		printf("is eating\n");
	else if (action == 2)
		printf("is sleeping\n");
	else if (action == 3)
		printf("is thinking\n");
	else if (action == 4)
		printf("died\n");
	printf("\n");
	pthread_mutex_unlock(lock);
}
