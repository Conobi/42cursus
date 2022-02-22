/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:15:13 by conobi            #+#    #+#             */
/*   Updated: 2022/02/22 15:44:13 by conobi           ###   ########lyon.fr   */
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

void	*routine(void *args)
{
	t_data	*data;
	t_philo	*philo;

	data = (t_data *)args;
	data->curr--;
	philo = &data->atrium[data->curr];
	pthread_mutex_lock(&data->debug_lock);
	printf("nº%d:\n", philo->id);
	printf("\ttid:  %d\n", (int) philo->tid);
	printf("---\n");
	pthread_mutex_unlock(&data->debug_lock);
// printf("\tfork: %d\n", (int) data->atrium[data->curr].fork);
	return (0);
}

short	birth(t_data *data)
{
	int		i;

	i = -1;
	data->atrium = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->atrium)
		return (-1);
	while (++i <= data->nb_philo)
	{
		data->atrium[i].id = i;
		pthread_mutex_init(&data->atrium[i].fork, NULL);
		pthread_mutex_lock(&data->atrium[i].fork);
		if (i % 2)
			pthread_mutex_unlock(&data->atrium[i].fork);
		data->atrium[i].last_eat = 0;
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
	printf("[%d]\n", data.nb_philo);
	birth(&data);
	pthread_mutex_init(&data.debug_lock, NULL);
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
	return (0);
}
