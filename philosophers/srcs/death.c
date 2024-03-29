/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:25:35 by conobi            #+#    #+#             */
/*   Updated: 2022/03/29 19:44:40 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_status(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->death_lock);
	ret = philo->data->somebody_died;
	pthread_mutex_unlock(&philo->death_lock);
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
		if (eat_delay >= data->starve_time && !death_status(&(data->atrium[i])))
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
