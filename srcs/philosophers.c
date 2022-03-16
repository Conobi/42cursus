/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:15:13 by conobi            #+#    #+#             */
/*   Updated: 2022/03/16 20:11:02 by conobi           ###   ########lyon.fr   */
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

static short	birth(t_data *data)
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
		data->atrium[i].id = i;
		data->atrium[i].data = data;
	}
	return (0);
}

static void	*routine(void *args)
{
	int	i;
	t_philo	*philo;

	philo = (t_philo *)args;
	// while (!philo->data->threads_ready)
	// 	;
	// printer(philo, "\e[39mis starting");
	i = 3;
	while (--i)
	{
		printer(philo, "\e[39mis sleeping");
		precise_usleep(philo->data->sleep_time * 1000, philo);
		// pthread_mutex_lock(&philo->eat_lock);
		// philo->last_meal = calc_ts(0);
		// pthread_mutex_unlock(&philo->eat_lock);
		printer(philo, "\e[39mis thinking");
	}
	philo->data->somebody_died = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5)
		return (print_help(argv));
	data.nb_philo = f_atoi(argv[1]);
	data.starve_time = f_atoi(argv[2]);
	data.meal_time = f_atoi(argv[3]);
	data.sleep_time = f_atoi(argv[4]);
	data.somebody_died = 0;
	data.threads_ready = 0;
	pthread_mutex_init(&data.death_lock, NULL);
	pthread_mutex_init(&data.lock, NULL);
	birth(&data);
	i = -1;
	printf("Zéparti\n");
	while (++i < data.nb_philo)
		pthread_create(&(data.atrium[i].tid), NULL,
			routine, &(data.atrium[i]));
	data.start_ts = calc_ts(0);
	printf("On défini les start...\n");
	i = -1;
	while (++i < data.nb_philo)
		data.atrium[i].last_meal = data.start_ts;
	data.threads_ready = 1;
	printf("On est ready\n");
	pthread_create(&(data.checker_tid), NULL, checker_thread, &data);
	death_checker(&data);
	// printf("Ah !\n");
	pthread_join(data.checker_tid, NULL);
	i = -1;
	while (++i < data.nb_philo)
		pthread_join(data.atrium[i].tid, NULL);
	death(&data);
	return (0);
}
