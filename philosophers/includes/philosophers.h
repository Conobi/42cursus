/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:14:10 by conobi            #+#    #+#             */
/*   Updated: 2022/03/29 19:44:29 by conobi           ###   ########lyon.fr   */
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
	pthread_t		checker_tid;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	t_philo			*atrium;
	double			start_ts;
	int				nb_philo;
	int				starve_time;
	int				meal_time;
	int				sleep_time;
	int				nb_meals;
	int				philos_done;
	int				dead_philo;
	int				death_ts;
	int				full_belly;
	int				somebody_died;
	int				threads_ready;
}	t_data;

typedef struct s_philo {
	pthread_t		tid;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	death_lock;
	int				id;
	int				nb_meals;
	double			last_meal;
	t_data			*data;
}	t_philo;

/* philosophers.c */
void	*routine_handler(void *args);

/* utils.c */
int		f_atoi(char *str);
double	calc_ts(double start_date);
void	precise_usleep(int time, t_philo *philo);
void	printer(t_philo *philo, char *message);
void	fork_hand(t_data *data, int id, short action);
int		death_status(t_philo *philo);

/* death.c */
void	death_checker(t_data *data);
void	*checker_thread(void *args);
void	death(t_data *data);
void	last_judgement(t_data *data);

/* init.c */
int		init_data(int argc, char **argv, t_data *data);
short	birth(t_data *data);
int		meal_status(t_data *data);

#endif
