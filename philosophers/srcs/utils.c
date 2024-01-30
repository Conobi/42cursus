/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 18:49:12 by conobi            #+#    #+#             */
/*   Updated: 2022/07/12 22:40:36 by conobi           ###   ########lyon.fr   */
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

void	printer(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->lock);
	if (!death_status(philo))
		printf("\e[90m%d \e[32m%d %s\n",
			(int)calc_ts(philo->data->start_ts), philo->id, message);
	pthread_mutex_unlock(&philo->data->lock);
}

void	precise_usleep(int time, t_philo *philo)
{
	struct timeval	initial_time;
	struct timeval	curr_time;
	double			initial_ts;
	double			curr_ts;

	philo += 0;
	gettimeofday(&initial_time, NULL);
	initial_ts = (initial_time.tv_sec * 1000 + initial_time.tv_usec / 1000);
	gettimeofday(&curr_time, NULL);
	curr_ts = (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
	while (curr_ts < (initial_ts + time) && !death_status(philo))
	{
		usleep(500);
		gettimeofday(&curr_time, NULL);
		curr_ts = (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
	}
}

void	fork_hand(t_data *data, int id, short action)
{
	if (action == 0 && !death_status(&(data->atrium[id])))
	{
		pthread_mutex_lock(&data->forks[id]);
		if (id == data->nb_philo - 1)
			pthread_mutex_lock(&data->forks[0]);
		else
			pthread_mutex_lock(&data->forks[id + 1]);
	}
	else if (!death_status(&(data->atrium[id])))
	{
		pthread_mutex_unlock(&data->forks[id]);
		if (id == data->nb_philo - 1)
			pthread_mutex_unlock(&data->forks[0]);
		else
			pthread_mutex_unlock(&data->forks[id + 1]);
	}
}
