/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:25:55 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/11 11:43:17 by dtolmaco         ###   ########.fr       */
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
	if (philo->data->num_philo == philo->data->philo_finish)
		philo->data->is_dead = 1;
}

int	check_if_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write);
	check_if_finish(philo);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	philo->time_passed = (get_time() - philo->start_time) \
	- philo->last_meal;
	if (philo->time_passed >= philo->data->time_to_die)
	{
		message("died", philo);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->write);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->write);
	return (1);
}
