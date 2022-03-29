/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:02:02 by conobi            #+#    #+#             */
/*   Updated: 2022/03/29 16:52:15 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_help(char **argv)
{
	printf("%s: Invalid arguments\n", argv[0]);
	printf("\e[92m\e[1mUSAGE:\e[0m %s", argv[0]);
	printf(" \e[96mnumber_of_philosophers time_to_die time_to_eat");
	printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\e[0m\n");
	return (1);
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (!(argc == 5 || argc == 6))
		return (print_help(argv));
	data->nb_philo = f_atoi(argv[1]);
	data->starve_time = f_atoi(argv[2]);
	data->meal_time = f_atoi(argv[3]);
	data->sleep_time = f_atoi(argv[4]);
	if (!data->nb_philo || !data->starve_time
		|| !data->meal_time || !data->sleep_time)
		return (print_help(argv));
	data->somebody_died = 0;
	data->threads_ready = 0;
	data->nb_meals = 0;
	if (argc == 6)
		data->nb_meals = f_atoi(argv[5]);
	data->philos_done = 0;
	data->full_belly = 0;
	return (0);
}

short	birth(t_data *data)
{
	int		i;

	data->atrium = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->atrium)
		return (-1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (-1);
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->atrium[i].eat_lock, NULL);
		pthread_mutex_init(&data->atrium[i].death_lock, NULL);
		data->atrium[i].id = i + 1;
		data->atrium[i].nb_meals = 0;
		data->atrium[i].data = data;
		data->atrium[i].last_meal = data->start_ts;
	}
	i = -1;
	while (++i < data->nb_philo)
		pthread_create(&(data->atrium[i].tid), NULL,
			routine_handler, &(data->atrium[i]));
	return (0);
}
