/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:25:35 by conobi            #+#    #+#             */
/*   Updated: 2022/03/16 19:47:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

short	death_status(t_philo *philo)
{
	short	ret;

	// pthread_mutex_lock(&philo->death_lock);
	pthread_mutex_lock(&philo->data->death_lock);
	ret = philo->data->somebody_died;
	pthread_mutex_unlock(&philo->data->death_lock);
	// pthread_mutex_unlock(&philo->death_lock);
	return (ret);
}

void	death_checker(t_data *data)
{
	data += 0;
	// int	i;
	// int	eat_delay;

	// i = -1;
	// while (++i < data->nb_philo)
	// {
	// 	// pthread_mutex_lock(&data->atrium[i].death_lock);
	// 	pthread_mutex_lock(&data->atrium[i].eat_lock);
	// 	eat_delay = calc_ts(0) - data->atrium[i].last_meal;
	// 	pthread_mutex_unlock(&data->atrium[i].eat_lock);
	// 	// printf(" (%d) ", eat_delay);
	// 	if (eat_delay >= data->starve_time && !death_status(&data->atrium[i]))
	// 	{
	// 		// printf("Alors %d >= %d\n", eat_delay, data->starve_time);
	// 		// pthread_mutex_lock(&data->atrium[i].death_lock);
	// 		pthread_mutex_lock(&data->death_lock);
	// 		data->somebody_died = 1;
	// 		pthread_mutex_unlock(&data->death_lock);
	// 		// pthread_mutex_unlock(&data->atrium[i].death_lock);
	// 		data->dead_philo = i;
	// 		data->death_ts = calc_ts(data->start_ts);
	// 	}
	// 	// else
	// 	// 	printf("Alors %f <= %d\n", calc_ts(0) - data->atrium[i].last_meal, data->starve_time);
	// 	// pthread_mutex_unlock(&data->atrium[i].death_lock);
	// }
}

void	*checker_thread(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	// while (!death_status(&data->atrium[0]))
	while (!data->somebody_died)
		death_checker(data);
	return (0);
}
