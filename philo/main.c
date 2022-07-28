/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:35:15 by rigel             #+#    #+#             */
/*   Updated: 2022/07/28 16:21:18 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*eating(t_philo *phi, pthread_mutex_t **first, pthread_mutex_t **second)
{
	pthread_mutex_lock(*first);
	if (!print_status("has taken a fork", phi))
		return (pthread_mutex_unlock(*first), NULL);
	pthread_mutex_lock(*second);
	if (!print_status("has taken a fork", phi))
		return (pthread_mutex_unlock(*second),
			pthread_mutex_unlock(*first), NULL);
	if (!print_status("is eating", phi))
		return (pthread_mutex_unlock(*second),
			pthread_mutex_unlock(*first), NULL);
	pthread_mutex_lock(&phi->arg->status);
	phi->last_meal = get_time();
	pthread_mutex_unlock(&phi->arg->status);
	if (!ft_sleep(phi, phi->arg->time_to_eat))
		return (pthread_mutex_unlock(*second),
			pthread_mutex_unlock(*first), NULL);
	(pthread_mutex_unlock(*second), pthread_mutex_unlock(*first));
	return ((void *)1);
}

void	*start_routine(void *philo)
{
	t_philo			*phi;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	phi = philo;
	pthread_mutex_lock(&*&phi->arg->status);
	if (phi->arg->death == 1)
		return (pthread_mutex_unlock(&phi->arg->status), NULL);
	pthread_mutex_unlock(&phi->arg->status);
	set_fork(phi, &first, &second);
	while (1)
	{
		if (!print_status("is thinking", phi))
			return (NULL);
		usleep(400);
		eating(phi, &first, &second);
		pthread_mutex_lock(&phi->arg->status);
		phi->meal_count += 1;
		pthread_mutex_unlock(&phi->arg->status);
		if (!print_status("is sleeping", phi))
			return (NULL);
		if (!ft_sleep(phi, phi->arg->time_to_sleep))
			return (NULL);
	}
	return ((void *)1);
}

int	check_death(long long *nb_finished, t_philo *phi, t_arg *arg)
{
	if (phi->meal_count >= arg->numb_must_eat)
		*nb_finished = *nb_finished + 1;
	if (get_time() - phi->last_meal >= arg->time_to_die)
	{
		phi->arg->death = 1;
		print_status_unchecked("died", phi);
		return (pthread_mutex_unlock(&arg->status), 0);
	}
	return (1);
}

int	ft_time_lord(t_arg *arg)
{
	t_philo		*phi;
	long long	nb_finished;

	while (1)
	{
		phi = arg->begin;
		nb_finished = 0;
		pthread_mutex_lock(&arg->status);
		while (phi)
		{
			if (!check_death(&nb_finished, phi, arg))
				return (0);
			phi = phi->next;
		}
		if (arg->argc == 6 && nb_finished == arg->phil_numb)
		{
			arg->death = 1;
			pthread_mutex_unlock(&arg->status);
			return (0);
		}
		pthread_mutex_unlock(&arg->status);
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	long long		i;
	t_arg			args;

	if (!set_check_args(argc, argv, &args) || !solo_die(&args))
		return (0);
	if (pthread_mutex_init(&args.status, NULL))
		return (printf("Mutex initialisation failed\n"), 0);
	pthread_mutex_lock(&args.status);
	i = 1;
	while (i <= args.phil_numb)
	{
		if (!set_philo(i, &args, &args.begin))
			return (set_philo_fail(&args));
		i++;
	}
	args.start_time = get_time();
	pthread_mutex_unlock(&args.status);
	ft_time_lord(&args);
	philo_clear(args.begin);
	pthread_mutex_destroy(&args.status);
}
