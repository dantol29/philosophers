/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:09:20 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/09 12:36:19 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(char *str, t_philo *philo)
{
	printf("%ld %d %s\n", get_time() - philo->start_time, \
	philo->id, str);
}

int	check_if_dead(t_philo *philo, int status)
{
	if (philo->ate == philo->data->must_eat && philo->data->must_eat != -1)
		philo->data->philo_finish += 1;
	if (philo->data->num_philo == philo->data->philo_finish)
		philo->data->is_dead = 1;
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&philo->data->waiter);
		return (0);
	}
	if (status == 1)
		philo->last_meal = get_time() - philo->start_time;
	if (status == 0)
		philo->last_meal = 0;
	if (philo->last_meal >= philo->data->time_to_die)
	{
		philo->data->is_dead = 1;
		message("died", philo);
		return (0);
	}
	return (1);
}

long	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec  / 1000);
}

void	wait_threads(pthread_t *threads, int size)
{
	int	i;
	
	i = 0;
	while (i < size)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	check_argv(int argc)
{
	if (argc < 5)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}