/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:07:52 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/09 18:37:39 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_philo *philo, t_data *data)
{
	int			i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->num_philo);
	if (data->num_philo == 1)
		pthread_create(&data->threads[0], NULL, one_philo, (void *)&philo[0]);
	else
	{
		while (i < data->num_philo)
		{
			pthread_create(&data->threads[i], NULL, live, (void *)&philo[i]);
			i++;
		}
	}
}

void	create_philosophers(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].start_time = 0;
		philo[i].last_meal = 0;
		philo[i].ate = 0;
		philo[i].time_passed = 0;
		philo[i].start_time = get_time();
		philo[i].last_meal = get_time() - philo->start_time;
		philo[i].left_fork = &data->forks[i];
		if (i + 1 == data->num_philo)
			philo[i].right_fork = &data->forks[0];
		else
			philo[i].right_fork = &data->forks[i + 1];
		philo[i].data = data;
		i++;
	}
	pthread_mutex_init(&data->waiter, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_data(t_data *data, char **argv, int argc)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = 0;
	data->must_eat = -1;
	data->philo_finish = 0;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
}

void	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philo)
	{
		pthread_mutex_destroy(&philo->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->data->waiter);
	if (philo->data->philo_finish == philo->data->num_philo)
		printf("All %d philosphers ate %d meals\n", \
		philo->data->num_philo, philo->data->must_eat);
	free(philo->data->forks);
	free(philo->data->threads);
}
