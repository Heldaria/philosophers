/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:35:15 by rigel             #+#    #+#             */
/*   Updated: 2022/07/25 14:35:47 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	print_status(char *str, t_philo *philos)
{
	pthread_mutex_lock(philos->arg->status);
	printf("%lu %i %s\n", get_time(), philos->number, str);
	pthread_mutex_unlock(philos->arg->status);
}

void	*start_routine(void *philo)
{
	t_philo	*const phi = philo;
	t_philo				*begin;

	printf("Start routine\n");
	begin = phi;
	pthread_mutex_lock(phi->arg->start_all);
	pthread_mutex_unlock(phi->arg->start_all);
	if (phi->number % 2)
	{
		pthread_mutex_lock(phi->fork);
		print_status("has taken a fork", phi);
		if (phi->next == NULL)
			pthread_mutex_lock(begin->next->fork);
		else
			pthread_mutex_lock(phi->next->fork);
		print_status("has taken a fork", phi);
	}
	else
	{
		if (phi->next == NULL)
			pthread_mutex_lock(begin->next->fork);
		else
			pthread_mutex_lock(phi->next->fork);
		print_status("has taken a fork", phi);
		pthread_mutex_lock(phi->fork);
		print_status("has taken a fork", phi);
	}
	print_status("is eating", phi);
	usleep(phi->arg->time_to_eat / 1000);
	phi->meal_count += 1;
	phi->last_meal = get_time();
	print_status("is sleeping", phi);
	usleep(phi->arg->time_to_sleep / 1000);
	return ((void *)1);
}

void	*ft_time_lord(void *philo)
{
	t_philo	*phi;
	t_philo	*begin;

	phi = (t_philo *)philo;
	begin = phi;
	while (begin->arg->death == 0)
	{
		phi = begin;
		pthread_mutex_lock(phi->arg->status);
		while (phi)
		{
			if (!(get_time() - phi->arg->time_passed - phi->last_meal <= phi->arg->time_to_die
					|| (phi->arg->argc == 6
					&& phi->meal_count <= phi->arg->numb_must_eat)))
			{
				phi->arg->death = 1;
				print_status("died", phi);
				return (0);
			}
			phi = phi->next;
		}
		pthread_mutex_unlock(phi->arg->status);
		usleep(200 / 1000);
	}
	return ((void *)1);
}

int	set_philo(int i, t_arg *args, t_philo **philos)
{
	t_philo	*new;

	new = ft_philonew(i, args);
	if (pthread_create(&new->thread, NULL, start_routine, new))
		return (printf("%s %i %s\n", "Philosopher", i, "thread creation failed"), 0);
	// if (pthread_mutex_init(&new->fork, NULL))
	// 	return (printf("Mutex initialisation failed\n"), 0);
	if (*philos == NULL)
		*philos = new;
	else
		ft_philoadd_back(philos, new);
	return (1);
}

int	main(int argc, char **argv)
{
	uint32_t		i;
	t_arg			*args;
	t_philo			*philos;

	philos = NULL;
	if (argc != 5 && argc != 6)
		return(printf("Invalid number of arguments\n"), 0);
	if (ft_ulong_atoi(argv[1]) <= 0)
		return(printf("Invalid number of philosopher(s)\n"), 0);
	args = malloc(sizeof(t_arg));
	if (!args)
		return (printf("Args malloc failed\n"), 0);
	args->phil_numb = ft_ulong_atoi(argv[1]);
	args->time_to_die = ft_ulong_atoi(argv[2]);
	args->time_to_eat = ft_ulong_atoi(argv[3]);
	args->time_to_sleep = ft_ulong_atoi(argv[4]);
	args->argc = argc;
	args->death = 0;
	if (argc == 6)
		args->numb_must_eat = ft_ulong_atoi(argv[5]);
	else
		args->numb_must_eat = 0;
	args->start_all = malloc(sizeof(pthread_mutex_t));
	if (!args->start_all)
		return(printf("Mutex malloc failed\n"), 0);
	if (pthread_mutex_init(args->start_all, NULL))
		return (printf("Mutex initialisation failed\n"), 0);
	args->status = malloc(sizeof(pthread_mutex_t));
	if (!args->start_all)
		return(printf("Mutex malloc failed\n"), 0);
	if (pthread_mutex_init(args->status, NULL))
		return (printf("Mutex initialisation failed\n"), 0);
	pthread_mutex_lock(args->start_all);
	i = 1;
	while (i <= ft_ulong_atoi(argv[1]))
	{
		if (!set_philo(i, args, &philos))
			return(printf("failed to iniate philosopher struct\n"), 0);
		i++;
	}
	args->time_passed = get_time();
	if (pthread_create(&args->time_lord, NULL, ft_time_lord, philos))
		return (printf("Time Lord thread creation failed\n"), 0);
	pthread_mutex_unlock(args->start_all);
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
