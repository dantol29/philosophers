/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:47:03 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/09 18:18:53 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_if_finish(t_philo *philo)
{
	if (philo->ate == philo->data->must_eat \
	&& philo->data->must_eat != -1 && philo->ate != -1)
	{
		philo->ate = -1;
		philo->data->philo_finish += 1;
	}
	else if (philo->data->num_philo == philo->data->philo_finish)
		philo->data->is_dead = 1;
}

static int	check_if_dead(t_philo *philo, int status)
{
	check_if_finish(philo);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->data->waiter);
		return (0);
	}
	if (status == 1)
		philo->time_passed = (get_time() - philo->start_time) \
	- philo->last_meal;
	if (status == 0)
		philo->last_meal = get_time() - philo->start_time;
	if (philo->time_passed >= philo->data->time_to_die)
	{
		philo->data->is_dead = 1;
		message("died", philo);
		return (0);
	}
	return (1);
}

static int	eat_sleep(t_philo *philo)
{
	if (philo->ate != -1)
		philo->ate += 1;
	message("is eating", philo);
	if (!check_if_dead(philo, 1))
		return (0);
	check_if_dead(philo, 0);
	pthread_mutex_unlock(&philo->data->waiter);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (!check_if_dead(philo, 1))
		return (0);
	message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	if (!check_if_dead(philo, 1))
		return (0);
	message("is thinking", philo);
	return (1);
}

void	*live(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_if_dead(philo, 1))
	{
		if (!check_if_dead(philo, 1))
			return (NULL);
		pthread_mutex_lock(philo->left_fork);
		if (!check_if_dead(philo, 1))
			return (NULL);
		message("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		if (!check_if_dead(philo, 1))
			return (NULL);
		message("has taken a fork", philo);
		pthread_mutex_lock(&philo->data->waiter);
		if (!check_if_dead(philo, 1))
			return (NULL);
		if (!eat_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;

	if (check_argv(argc, argv) == 1)
		return (1);
	init_data(&data, argv, argc);
	init_forks(&data);
	philo = malloc(sizeof(t_philo) * data.num_philo);
	if (philo == NULL)
		return (1);
	create_philosophers(philo, &data);
	start_threads(philo, &data);
	wait_threads(data.threads, data.num_philo);
	free_all(philo);
	free(philo);
}
