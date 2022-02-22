/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:15:13 by conobi            #+#    #+#             */
/*   Updated: 2022/02/22 19:45:37 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_help(char **argv)
{
	printf("%s: Invalid arguments\n", argv[0]);
	printf("\e[92m\e[1mUSAGE:\e[0m %s", argv[0]);
// printf(" \e[96m\e[4mnumber_of_philosophers time_to_die time_to_eat");
// printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\e[0m\n");
	printf(" nb_philo\n");
	return (0);
}

static void	fork_hand(t_data *data, int id, short action)
{
	if (action == 0)
	{
		pthread_mutex_lock(&data->atrium[id].fork);
		if (id == data->nb_philo - 1)
			pthread_mutex_lock(&data->atrium[0].fork);
		else
			pthread_mutex_lock(&data->atrium[id + 1].fork);
	}
	else
	{
		pthread_mutex_unlock(&data->atrium[id].fork);
		if (id == data->nb_philo - 1)
			pthread_mutex_unlock(&data->atrium[0].fork);
		else
			pthread_mutex_unlock(&data->atrium[id + 1].fork);
	}
}

static void	*routine(void *args)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)args;
	data->curr--;
	philo = &data->atrium[data->curr];
	while (philo->is_alive)
	{
		if (philo->id % 2)
		{
			printer(calc_ts(data->start_ts), philo->id, 2, &data->lock);
			usleep(data->sleep_time * 1e+3);
		}
		fork_hand(data, philo->id, 0);
		printer(calc_ts(data->start_ts), philo->id, 0, &data->lock);
		printer(calc_ts(data->start_ts), philo->id, 1, &data->lock);
		usleep(data->meal_time * 1e+3);
		fork_hand(data, philo->id, 1);
		if (!(philo->id % 2))
		{
			printer(calc_ts(data->start_ts), philo->id, 2, &data->lock);
			usleep(data->sleep_time * 1e+3);
		}
		printer(calc_ts(data->start_ts), philo->id, 3, &data->lock);
		philo->is_alive = 1;
	}
	return (0);
}

static short	birth(t_data *data)
{
	int		i;

	i = -1;
	data->atrium = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->atrium)
		return (-1);
	while (++i <= data->nb_philo)
	{
		data->atrium[i].id = i;
		data->atrium[i].last_meal = 0;
		pthread_mutex_init(&data->atrium[i].fork, NULL);
		data->atrium[i].is_alive = 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 2)
		return (print_help(argv));
	data.nb_philo = f_atoi(argv[1]);
	data.curr = data.nb_philo;
	data.start_ts = calc_ts(0);
	data.meal_time = 70;
	data.sleep_time = 50;
	data.starve_time = 150;
	printf("(c Squide game enfaite, il y a %d joueurs.......)\n", data.nb_philo);
	birth(&data);
	pthread_mutex_init(&data.lock, NULL);
	i = -1;
	while (++i < data.nb_philo)
		pthread_create(&(data.atrium[i].tid), NULL,
			routine, &data);
	i = -1;
	while (++i < data.nb_philo)
		pthread_join(data.atrium[i].tid, NULL);
	i = -1;
	while (++i < data.nb_philo)
		pthread_mutex_destroy(&(data.atrium[data.curr].fork));
	pthread_mutex_destroy(&data.lock);
	return (0);
}
