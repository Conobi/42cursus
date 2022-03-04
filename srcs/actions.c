/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:32:07 by conobi            #+#    #+#             */
/*   Updated: 2022/03/04 19:36:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	bedtime(t_philo *philo)
{
	// if (philo->data->somebody_died)
	// 	return ;
	// printer(calc_ts(philo->data->start_ts), philo->id, 2, &philo->data->lock);
	if (philo->data->somebody_died)
		return ;
	printf("\e[90m%d \e[32m%d \e[39mis sleeping\n",
		(int)calc_ts(philo->data->start_ts), philo->id);
	death_usleep(philo->data->sleep_time * 1000, philo->data);
	// usleep(philo->data->sleep_time * 1000);
}

void	eat(t_philo *philo)
{
	if (philo->data->somebody_died)
		return ;
	fork_hand(philo->data, philo->id, 0);
	// printer(calc_ts(philo->data->start_ts),
	// 	philo->id, 0, &philo->data->lock);
	printf("\e[90m%d \e[32m%d \e[39mhas taken a fork\n",
		(int)calc_ts(philo->data->start_ts), philo->id);
	printf("\e[90m%d \e[32m%d \e[39mis eating\n",
		(int)calc_ts(philo->data->start_ts), philo->id);
	// printer(calc_ts(philo->data->start_ts),
	// 	philo->id, 1, &philo->data->lock);
	death_usleep(philo->data->meal_time * 1000, philo->data);
	// usleep(philo->data->meal_time * 1000);
	fork_hand(philo->data, philo->id, 1);
	philo->last_meal = calc_ts(philo->data->start_ts) - philo->last_meal;
	// philo->last_meal = calc_ts(philo->last_meal) - calc_ts(philo->data->start_ts);
}
