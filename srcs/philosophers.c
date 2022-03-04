/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:15:13 by conobi            #+#    #+#             */
/*   Updated: 2022/03/04 19:05:15 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_help(char **argv)
{
	printf("%s: Invalid arguments\n", argv[0]);
	printf("\e[92m\e[1mUSAGE:\e[0m %s", argv[0]);
	printf(" \e[96mnumber_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\e[0m\n");
	// printf(" nb_philo\n");
	return (1);
}

void	fork_hand(t_data *data, int id, short action)
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
	// t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->somebody_died)
	{
		// data = philo->data;
		// data = (t_data *)args;
		// data->curr--;
		// philo = &data->atrium[data->curr];
		if (philo->id % 2)
		{
			bedtime(philo);
			if (philo->data->somebody_died)
				return (0);
			printf("\e[90m%d \e[32m%d \e[39mis thinking\n",
				(int)calc_ts(philo->data->start_ts), philo->id);
			eat(philo);
		}
		else
		{
			eat(philo);
			bedtime(philo);
			if (philo->data->somebody_died)
				return (0);
			printf("\e[90m%d \e[32m%d \e[39mis thinking\n",
				(int)calc_ts(philo->data->start_ts), philo->id);
			// printf("\e[90m%d \e[32m%d \e[39mis thinking (%d)\n",
			// 	(int)calc_ts(philo->data->start_ts), philo->id, philo->last_meal);
		}
	}
	// printf("\e[90m%d \e[32m%d \e[39mis thinking\n",
	// 	(int)calc_ts(philo->data->start_ts), philo->id);
	// if (philo->data->somebody_died)
	// 	printf("wowowow\n");
	return (0);
}

static short	birth(t_data *data)
{
	int		i;

	i = -1;
	data->atrium = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->atrium)
		return (-1);
	while (++i < data->nb_philo)
	{
		data->atrium[i].id = i;
		data->atrium[i].last_meal = calc_ts(data->start_ts);
		data->atrium[i].data = data;
		pthread_mutex_init(&data->atrium[i].fork, NULL);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5)
		return (print_help(argv));
	data.nb_philo = f_atoi(argv[1]);
	data.curr = data.nb_philo;
	data.start_ts = calc_ts(0);
	data.starve_time = f_atoi(argv[2]);
	data.meal_time = f_atoi(argv[3]);
	data.sleep_time = f_atoi(argv[4]);
	data.somebody_died = 0;
	birth(&data);
	pthread_mutex_init(&data.lock, NULL);
	i = -1;
	while (++i < data.nb_philo)
		pthread_create(&(data.atrium[i].tid), NULL,
			routine, &(data.atrium[i]));
	i = -1;
	while (++i < data.nb_philo && !data.somebody_died)
		pthread_join(data.atrium[i].tid, NULL);
	i = -1;
	while (++i < data.nb_philo)
	{
		pthread_detach(data.atrium[i].tid);
		pthread_mutex_destroy(&(data.atrium[i].fork));
	}
	// pthread_mutex_unlock(&data.lock);
	pthread_mutex_destroy(&data.lock);
	free(data.atrium);
	usleep(1000);
	if (data.somebody_died)
		printf("\e[90m%d \e[32m%d \e[39m\e[91mdied\e[39m\n",
			data.death_ts, data.dead_body);
	printf("T'es finito\n");
	return (0);
}
