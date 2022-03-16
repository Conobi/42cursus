/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:32:07 by conobi            #+#    #+#             */
/*   Updated: 2022/03/16 12:12:15 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	bedtime(t_philo *philo)
// {
// 	printf("\e[90m%d \e[32m%d \e[39mis sleeping\n",
// 		(int)calc_ts(philo->data->start_ts), philo->id);
// 	death_usleep(philo->data->sleep_time * 1000, philo, 0);
// }

// void	eat(t_philo *philo)
// {
// 	fork_hand(philo->data, philo->id, 0);
// 	if (philo->data->somebody_died)
// 		return ;
// 	philo->last_meal = calc_ts(0);
// 	printf("\e[90m%d \e[32m%d \e[39mhas taken a fork\n",
// 		(int)calc_ts(philo->data->start_ts), philo->id);
// 	printf("\e[90m%d \e[32m%d \e[39mis eating\n",
// 		(int)calc_ts(philo->data->start_ts), philo->id);
// 	death_usleep(philo->data->meal_time * 1000, philo, 1);
// 	fork_hand(philo->data, philo->id, 1);
// }

void	death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_unlock(&data->atrium[i].eat_lock);
		pthread_mutex_unlock(&data->atrium[i].death_lock);
		pthread_detach(data->atrium[i].tid);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->atrium[i].eat_lock);
		pthread_mutex_destroy(&data->atrium[i].death_lock);
	}
	if (data->somebody_died)
		printf("\e[90m%d \e[32m%d \e[39m\e[91mdied\e[39m\n",
			data->death_ts, data->dead_philo);
}
