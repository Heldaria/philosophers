/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:35:15 by rigel             #+#    #+#             */
/*   Updated: 2022/07/26 17:50:50 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

// int	sleep(t_philo *philo, uint64_t duration)
// {
// 	const uint64_t	end = get_time() + duration;

// 	while (get_time() < end)
// 	{
// 		pthread_mutex_lock(&philo->arg->status);
// 		if (philo->arg->death)
// 			return (pthread_mutex_unlock(&philo->arg->status), 0);
// 	}
// }

uint64_t	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

int	print_status(char *str, t_philo *philos)
{
	pthread_mutex_lock(&philos->arg->status);
	if (philos->arg->death)
		return (pthread_mutex_unlock(&philos->arg->status), 0);
	printf("%lu %i %s\n", get_time() - philos->arg->start_time, philos->number, str);
	pthread_mutex_unlock(&philos->arg->status);
	return (1);
}

void	*start_routine(void *philo)
{
	t_philo	*const phi = philo;

	pthread_mutex_lock(&*&phi->arg->start_all);
	pthread_mutex_unlock(&phi->arg->start_all);
	while (1)
	{
		if (phi->number % 2)
		{
			pthread_mutex_lock(&phi->fork);
			if (!print_status("has taken a fork", phi))
				return (NULL);
			if (phi->next == NULL)
				pthread_mutex_lock(&phi->arg->begin->next->fork);
			else
				pthread_mutex_lock(&phi->next->fork);
			if (!print_status("has taken a fork", phi))
				return (NULL);
		}
		else
		{
			if (phi->next == NULL)
				pthread_mutex_lock(&phi->arg->begin->next->fork);
			else
				pthread_mutex_lock(&phi->next->fork);
			if (!print_status("has taken a fork", phi))
				return (NULL);
			pthread_mutex_lock(&phi->fork);
			if (!print_status("has taken a fork", phi))
				return (NULL);
		}
		if (!print_status("is eating", phi))
			return (NULL);
		phi->last_meal = get_time();
		usleep(phi->arg->time_to_eat / 1000);
		phi->meal_count += 1;
		if (!print_status("is sleeping", phi))
			return (NULL);
		usleep(phi->arg->time_to_sleep / 1000);
	}
	return ((void *)1);
}

int	ft_time_lord(t_arg *arg)
{
	t_philo	*phi;

	while (arg->death == 0)
	{
		phi = arg->begin;
		pthread_mutex_lock(&arg->status);
		while (phi)
		{
			if (!(get_time() - phi->arg->start_time - phi->last_meal <= phi->arg->time_to_die
					|| (phi->arg->argc == 6
					&& phi->meal_count <= phi->arg->numb_must_eat)))
			{
				phi->arg->death = 1;
				print_status("died", phi);
				return (0);
			}
			phi = phi->next;
		}
		pthread_mutex_unlock(&arg->status);
		usleep(200 / 1000);
	}
	return (1);
}

int	set_philo(int i, t_arg *args, t_philo **philos)
{
	t_philo	*new;

	new = ft_philonew(i, args);
	if (pthread_create(&new->thread, NULL, start_routine, new))
		return (printf("%s %i %s\n", "Philosopher", i, "thread creation failed"), 0);
	// \if (pthread_mutex_init(&new->fork, NULL))
	// \	return (printf("Mutex initialisation failed\n"), 0);
	ft_philoadd_back(philos, new);
	return (1);
}

static int	mutex_init(t_arg *args)
{
	if (pthread_mutex_init(&args->start_all, NULL))
		return (printf("Mutex initialisation failed\n"), 0);
	if (pthread_mutex_init(&args->status, NULL))
		return (printf("Mutex initialisation failed\n"),
			pthread_mutex_destroy(&*&args->start_all), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	uint32_t		i;
	t_arg			args;

	if (argc != 5 && argc != 6)
		return(printf("Invalid number of arguments\n"), 0);
	if (ft_ulong_atoi(argv[1]) <= 0)
		return(printf("Invalid number of philosopher(s)\n"), 0);
	args.phil_numb = ft_ulong_atoi(argv[1]);
	args.time_to_die = ft_ulong_atoi(argv[2]);
	args.time_to_eat = ft_ulong_atoi(argv[3]);
	args.time_to_sleep = ft_ulong_atoi(argv[4]);
	args.argc = argc;
	args.death = 0;
	args.begin = NULL;
	if (argc == 6)
		args.numb_must_eat = ft_ulong_atoi(argv[5]);
	else
		args.numb_must_eat = 0;
	if (!mutex_init(&args))
		return (1);
	pthread_mutex_lock(&args.start_all);
	i = 1;
	while (i <= args.phil_numb)
	{
		if (!set_philo(i, &args, &args.begin))
			return(printf("failed to iniate philosopher struct\n"), /* free la liste */ 0);
		i++;
	}
	args.start_time = get_time();
	// if (pthread_create(&args->time_lord, NULL, ft_time_lord, philos))
	// 	return (printf("Time Lord thread creation failed\n"), 0);
	pthread_mutex_unlock(&args.start_all);
	ft_time_lord(&args);
}

// int	main(void)
// {
// 	t_philo	*new;
// 	t_philo	**philos;

// 	new = ft_philonew(1, NULL);
// 	philos = NULL;
// 	ft_philoadd_back(philos, new);
// 	return (0);
// }
