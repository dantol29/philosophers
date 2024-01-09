/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:08:04 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/09 12:35:55 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				must_eat;
	int				philo_finish;
	int				is_dead;
	pthread_mutex_t *forks;
	pthread_mutex_t waiter;
	pthread_t		*threads;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	long			start_time;
	long			last_meal;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;
// life of philosophers
void	*live(void *data);

// memory
void	init_data(t_data *data, char **argv, int argc);
void	init_forks(t_data *data);
void	create_philosophers(t_philo *philo, t_data *data);
void	start_threads(t_philo *philo, t_data *data);
void	free_all(t_philo *philo);

// utils
int		ft_atoi(const char *str);
int		check_argv(int argc);
void	wait_threads(pthread_t *threads, int size);
long	get_time();
int		check_if_dead(t_philo *philo, int status);
void	message(char *str, t_philo *philo);

#endif