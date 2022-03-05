/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:12 by conobi            #+#    #+#             */
/*   Updated: 2022/03/05 02:24:26 by conobi           ###   ########lyon.fr   */
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
		pthread_mutex_unlock(&(data->atrium[dead_philo].fork));
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

void	death_usleep(int msec, t_philo *philo, short eating)
{
	int	i;
	int	j;

	i = 0;
	while (i <= msec && !philo->data->somebody_died)
	{
		j = -1;
		while (++j < philo->data->nb_philo && !philo->data->somebody_died)
		{
			pthread_mutex_lock(&philo->data->lock);
			if (calc_ts(0) - philo->data->atrium[j].last_meal
				>= philo->data->starve_time
				&& !eating)
				kill_everybody(philo->data, j);
			pthread_mutex_unlock(&philo->data->lock);
		}
		i += 1000;
		usleep(1000);
	}
}
		// pthread_mutex_lock(&data->lock);

		// pthread_mutex_unlock(&data->lock);
// death_usleep:
			// if (data->atrium[j].last_meal >= data->starve_time)
