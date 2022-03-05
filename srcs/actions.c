/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:32:07 by conobi            #+#    #+#             */
/*   Updated: 2022/03/05 02:25:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	bedtime(t_philo *philo)
{
	if (philo->data->somebody_died)
		return ;
	printf("\e[90m%d \e[32m%d \e[39mis sleeping\n",
		(int)calc_ts(philo->data->start_ts), philo->id);
	death_usleep(philo->data->sleep_time * 1000, philo, 0);
}

void	eat(t_philo *philo)
{
	fork_hand(philo->data, philo->id, 0);
	if (philo->data->somebody_died)
		return ;
	philo->last_meal = calc_ts(0);
	printf("\e[90m%d \e[32m%d \e[39mhas taken a fork\n",
		(int)calc_ts(philo->data->start_ts), philo->id);
	printf("\e[90m%d \e[32m%d \e[39mis eating\n",
		(int)calc_ts(philo->data->start_ts), philo->id);
	death_usleep(philo->data->meal_time * 1000, philo, 1);
	fork_hand(philo->data, philo->id, 1);
}
