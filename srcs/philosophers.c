/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:15:13 by conobi            #+#    #+#             */
/*   Updated: 2022/03/29 19:42:53 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	routine_odd(t_philo *philo)
{
	fork_hand(philo->data, philo->id - 1, 0);
	printer(philo, "\e[39mhas taken a fork");
	printer(philo, "\e[39mis eating");
	precise_usleep(philo->data->meal_time, philo);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = calc_ts(0);
	pthread_mutex_unlock(&philo->eat_lock);
	fork_hand(philo->data, philo->id - 1, 1);
	printer(philo, "\e[39mis sleeping");
	precise_usleep(philo->data->sleep_time, philo);
	printer(philo, "\e[39mis thinking");
}

static void	routine_even(t_philo *philo)
{
	printer(philo, "\e[39mis sleeping");
	precise_usleep(philo->data->sleep_time, philo);
	printer(philo, "\e[39mis thinking");
	fork_hand(philo->data, philo->id - 1, 0);
	printer(philo, "\e[39mhas taken a fork");
	printer(philo, "\e[39mis eating");
	precise_usleep(philo->data->meal_time, philo);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = calc_ts(0);
	pthread_mutex_unlock(&philo->eat_lock);
	fork_hand(philo->data, philo->id - 1, 1);
}

short	meal_checker(t_philo *philo)
{
	if (philo->nb_meals >= philo->data->nb_meals && philo->data->nb_meals)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->philos_done++;
		pthread_mutex_unlock(&philo->data->lock);
	}
	if (meal_status(philo->data) >= philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->full_belly = 1;
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	return (0);
}

void	*routine_handler(void *args)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->threads_ready)
		;
	i = 3;
	while (!death_status(philo))
	{
		if (philo->id % 2)
			routine_odd(philo);
		else
			routine_even(philo);
		philo->nb_meals++;
		if (meal_checker(philo))
			break ;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = init_data(argc, argv, &data);
	if (i)
		return (i);
	pthread_mutex_init(&data.lock, NULL);
	birth(&data);
	data.start_ts = calc_ts(0);
	i = -1;
	while (++i < data.nb_philo)
	{
		pthread_mutex_lock(&data.atrium[i].eat_lock);
		data.atrium[i].last_meal = data.start_ts;
		pthread_mutex_unlock(&data.atrium[i].eat_lock);
	}
	data.threads_ready = 1;
	checker_thread(&data);
	i = -1;
	while (++i < data.nb_philo)
		pthread_join(data.atrium[i].tid, NULL);
	last_judgement(&data);
	return (0);
}
