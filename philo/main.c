/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:47:03 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/09 12:24:29 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_sleep(t_philo *philo)
{
	if (!check_if_dead(philo, 1))
		return (0);
	check_if_dead(philo, 0);
	message("is eating", philo);
	usleep(philo->data->time_to_eat * 1000);
	philo->ate += 1;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (!check_if_dead(philo, 1))
		return (0);
	message("is sleeping", philo);
	usleep(philo->data->time_to_sleep * 1000);
	if (!check_if_dead(philo, 1))
		return (0);
	message("is thinking", philo);
	return (1);
}

void	*live(void *data)
{
	t_philo 		*philo;

	philo = (t_philo *)data;
	philo->start_time = get_time();
	while (check_if_dead(philo, 1))
	{
		if (!check_if_dead(philo, 1))
			return (NULL);
		pthread_mutex_lock(&philo->data->waiter);
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
		pthread_mutex_unlock(&philo->data->waiter);
		if (!eat_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;

	check_argv(argc);
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
