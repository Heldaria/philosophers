/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:29:10 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/27 15:59:11 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	ft_sleep(t_philo *philo, uint64_t duration)
{
	const uint64_t	end = get_time() + duration;

	while (get_time() < end)
	{
		pthread_mutex_lock(&philo->arg->status);
		if (philo->arg->death)
			return (pthread_mutex_unlock(&philo->arg->status), 0);
		pthread_mutex_unlock(&philo->arg->status);
		usleep(200);
	}
	return (1);
}

uint64_t	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	print_status_unchecked(char *str, t_philo *philos)
{
	printf("%lu %i %s\n", get_time() - philos->arg->start_time,
		philos->number, str);
}

int	print_status(char *str, t_philo *philos)
{
	pthread_mutex_lock(&philos->arg->status);
	if (philos->arg->death)
		return (pthread_mutex_unlock(&philos->arg->status), 0);
	print_status_unchecked(str, philos);
	pthread_mutex_unlock(&philos->arg->status);
	return (1);
}

int	set_philo_fail(t_arg *args)
{
	printf("Failed to iniate philosopher struct\n");
	args->death = 1;
	pthread_mutex_unlock(&args->status);
	philo_clear(args->begin);
	pthread_mutex_destroy(&args->status);
	return (0);
}
