/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:25:35 by conobi            #+#    #+#             */
/*   Updated: 2022/03/29 16:48:04 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mut_status(pthread_mutex_t *lock, int value)
{
	int	ret;

	pthread_mutex_lock(lock);
	ret = value;
	pthread_mutex_unlock(lock);
	return (ret);
}

void	death_checker(t_data *data)
{
	int	i;
	int	eat_delay;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->atrium[i].eat_lock);
		eat_delay = calc_ts(0) - data->atrium[i].last_meal;
		pthread_mutex_unlock(&data->atrium[i].eat_lock);
		if (eat_delay >= data->starve_time
			&& !mut_status(&(&data->atrium[i])->death_lock,
				data->somebody_died))
		{
			data->dead_philo = data->atrium[i].id;
			i = -1;
			while (++i < data->nb_philo)
				pthread_mutex_lock(&data->atrium[i].death_lock);
			data->somebody_died = 1;
			i = -1;
			while (++i < data->nb_philo)
				pthread_mutex_unlock(&data->atrium[i].death_lock);
			data->death_ts = calc_ts(data->start_ts);
			death(data);
		}
	}
}

void	*checker_thread(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (!data->somebody_died)
		death_checker(data);
	return (0);
}

void	death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_unlock(&data->atrium[i].eat_lock);
		pthread_mutex_unlock(&data->atrium[i].death_lock);
	}
	pthread_mutex_lock(&data->lock);
	if (data->somebody_died && !data->full_belly)
		printf("\e[90m%d \e[32m%d \e[39m\e[91mdied\e[39m\n",
			data->death_ts, data->dead_philo);
	pthread_mutex_unlock(&data->lock);
}

void	last_judgement(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->atrium[i].eat_lock);
		pthread_mutex_destroy(&data->atrium[i].death_lock);
	}
	free(data->atrium);
	free(data->forks);
}
