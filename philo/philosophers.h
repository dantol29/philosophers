/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:08:04 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/11 12:30:37 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				must_eat;
	int				philo_finish;
	int				is_dead;
	int				*forks_state;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				ate;
	long			start_time;
	long			last_meal;
	long			time_passed;
	t_data			*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

void	*live(void *data);
int		check_if_dead(t_philo *philo);

// memory
void	init_data(t_data *data, char **argv, int argc);
void	init_forks(t_data *data);
void	create_philosophers(t_philo *philo, t_data *data);
void	start_threads(t_philo *philo, t_data *data);
void	free_all(t_philo *philo);

// utils
long	ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
int		check_argv(int argc, char **argv);
void	wait_threads(pthread_t *threads, int size);
long	get_time(void);
void	message(char *str, t_philo *philo);
int		ft_usleep(t_philo *philo, size_t milliseconds);

#endif