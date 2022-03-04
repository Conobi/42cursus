/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:14:10 by conobi            #+#    #+#             */
/*   Updated: 2022/02/25 17:12:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_data {
	pthread_mutex_t	lock;
	t_philo			*atrium;
	double			start_ts;
	int				nb_philo;
	int				starve_time;
	int				meal_time;
	int				sleep_time;
	int				curr;
	short			somebody_died;
	int				dead_body;
	int				death_ts;
}	t_data;

typedef struct s_philo {
	pthread_mutex_t	fork;
	pthread_t		tid;
	int				id;
	int				last_meal;
	t_data			*data;
}	t_philo;

/* philosophers.c */
void	fork_hand(t_data *data, int id, short action);

/* utils.c */
int		f_atoi(char *str);
double	calc_ts(double start_date);
void	printer(int ts, int id, short action, pthread_mutex_t *lock);
// void	printer(int ts, int id, short action, pthread_mutex_t *lock, short died);
void	death_usleep(int usec, t_data *data);

/* actions.c */
void	bedtime(t_philo *philo);
void	eat(t_philo *philo);

#endif
