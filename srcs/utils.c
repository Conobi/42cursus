/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:12 by conobi            #+#    #+#             */
/*   Updated: 2022/03/04 19:58:13 by conobi           ###   ########lyon.fr   */
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
	printf("\e[90m%d \e[32m%d \e[39m", ts, id);
	if (action == 0)
		printf("has taken a fork\n");
	else if (action == 1)
		printf("is eating\n");
	else if (action == 2)
		printf("is sleeping\n");
	else if (action == 3)
		printf("is thinking\n");
	else if (action == 4)
		printf("\e[91mdied\e[39m\n");
	pthread_mutex_unlock(lock);
}

void	kill_everybody(t_data *data, int dead_philo)
{
	int	ts;
	int	i;

	ts = (int)calc_ts(data->start_ts);
	data->somebody_died = 1;
	data->dead_body = dead_philo;
	data->death_ts = ts;
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_unlock(&(data->atrium[dead_philo].fork));
	}
}

// kill_everybody:
	// printer(calc_ts(data->start_ts),
	// data->atrium[dead_philo].id, 4, &data->lock);
	// i = -1;
	// while (++i < data->nb_philo)
	// {
	// 	pthread_mutex_unlock(&(data->atrium[dead_philo].fork));
	// 	pthread_mutex_destroy(&(data->atrium[dead_philo].fork));
	// 	pthread_detach(data->atrium[i].tid);
	// }

void	death_usleep(int msec, t_data *data)
{
	int	i;
	// int	j;
	data += 0;

	i = -1;
	while (i <= msec)
	{
		i += 1000;
		usleep(1000);
	}
}
		// j = -1;
		// pthread_mutex_lock(&data->lock);
		// while (++j < data->nb_philo && !data->somebody_died)
		// {
		// 	// if (!data->somebody_died)
		// 	if (data->atrium[j].last_meal >= data->starve_time)
		// 		kill_everybody(data, j);
		// 	// printf("%d: %d & %d\n", data->atrium[j].id, data->atrium[j].last_meal, data->starve_time);
		// }
		// pthread_mutex_unlock(&data->lock);
// death_usleep:
			// if (data->atrium[j].last_meal >= data->starve_time)
