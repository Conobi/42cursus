/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:14:10 by conobi            #+#    #+#             */
/*   Updated: 2022/02/22 15:26:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <time.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo {
	pthread_mutex_t	fork;
	pthread_t		tid;
	int				id;
	int				last_eat;
}	t_philo;

typedef struct s_data {
	pthread_mutex_t	debug_lock;
	t_philo			*atrium;
	int				nb_philo;
	int				curr;
}	t_data;

/* utils.c */
int	f_atoi(char *str);

#endif
