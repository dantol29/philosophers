/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:19:23 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/09 17:52:02 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	corner_cases(char **argv, int argc)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 \
	|| ft_atoi(argv[3]) < 1 || ft_atoi (argv[4]) < 1)
		return (1);
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("All philosophers ate their meal\n");
		return (1);
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(ft_atoi(argv[4]));
		printf("%d 1 died\n", ft_atoi(argv[2]));
		return (1);
	}
	return (0);
}

int	check_argv(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc > 6 || argc < 5)
		return (1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) > 200)
		return (1);
	if (corner_cases(argv, argc) == 1)
		return (1);
	return (0);
}
