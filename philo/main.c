/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:47:03 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/10 15:29:07 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	left_fork(t_philo *philo)
{
	while (philo->data->is_dead == 0)
	{
		if (philo->data->forks_state[philo->id - 1] == 1)
			check_if_dead(philo);
		else
		{
			pthread_mutex_lock(philo->left_fork);
			philo->data->forks_state[philo->id - 1] = 1;
			message("has taken a fork", philo);
			return (0);
		}
	}
	return (1);
}

static int	right_fork(t_philo *philo)
{
	int	fork_index;

	fork_index = philo->id;
	if (philo->id == philo->data->num_philo)
		fork_index = 0;
	while (philo->data->is_dead == 0)
	{
		if (philo->data->forks_state[fork_index] == 1)
			check_if_dead(philo);
		else
		{
			pthread_mutex_lock(philo->right_fork);
			philo->data->forks_state[fork_index] = 1;
			message("has taken a fork", philo);
			return (0);
		}
	}
	return (1);
}

static int	eat_sleep(t_philo *philo)
{
	if (philo->ate != -1)
		philo->ate += 1;
	message("is eating", philo);
	philo->last_meal = get_time() - philo->start_time;
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->id == philo->data->num_philo)
		philo->data->forks_state[0] = 0;
	else
		philo->data->forks_state[philo->id] = 0;
	pthread_mutex_unlock(philo->left_fork);
	philo->data->forks_state[philo->id - 1] = 0;
	message("is sleeping", philo);
	ft_usleep(philo, philo->data->time_to_sleep);
	message("is thinking", philo);
	return (0);
}

void	*live(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 1);
	while (philo->data->is_dead == 0)
	{
		if (left_fork(philo) == 1)
			return (NULL);
		if (right_fork(philo) == 1)
			return (NULL);
		if (eat_sleep(philo) == 1)
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
