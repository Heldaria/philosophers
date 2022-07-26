/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:35:15 by rigel             #+#    #+#             */
/*   Updated: 2022/07/26 21:51:57 by llepiney         ###   ########.fr       */
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
	printf("%lu %i %s\n", get_time() - philos->arg->start_time, philos->number, str);
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

void	*start_routine(void *philo)
{
	t_philo	*const phi = philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	pthread_mutex_lock(&*&phi->arg->status);
	if (phi->arg->death == 1)
		return (pthread_mutex_unlock(&phi->arg->status), NULL);
	pthread_mutex_unlock(&phi->arg->status);
	if  (phi->number % 2)
	{
		first = &phi->fork;
		if (phi->next == NULL)
			second = &phi->arg->begin->fork;
		else
			second = &phi->next->fork;
	}
	else
	{
		second = &phi->fork;
		if (phi->next == NULL)
			first = &phi->arg->begin->fork;
		else
			first = &phi->next->fork;
	}
	while (1)
	{
		if (!print_status("is thinking", phi))
			return (NULL);
		usleep(400);
		pthread_mutex_lock(first);
		if (!print_status("has taken a fork", phi))
			return (pthread_mutex_unlock(first), NULL);
		pthread_mutex_lock(second);
		if (!print_status("has taken a fork", phi))
			return (pthread_mutex_unlock(second), pthread_mutex_unlock(first), NULL);
		if (!print_status("is eating", phi))
			return (pthread_mutex_unlock(second), pthread_mutex_unlock(first), NULL);
		pthread_mutex_lock(&phi->arg->status);
		phi->last_meal = get_time();
		pthread_mutex_unlock(&phi->arg->status);
		if (!ft_sleep(phi, phi->arg->time_to_eat))
			return(pthread_mutex_unlock(second), pthread_mutex_unlock(first),NULL);
		(pthread_mutex_unlock(second), pthread_mutex_unlock(first));
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

int	ft_time_lord(t_arg *arg)
{
	t_philo	*phi;
	size_t	nb_finished;

	while (1)
	{
		phi = arg->begin;
		nb_finished = 0;
		pthread_mutex_lock(&arg->status);
		while (phi)
		{
			if (phi->meal_count >= arg->numb_must_eat)
				nb_finished++;
			if (get_time() - phi->last_meal >= arg->time_to_die)
			{
				phi->arg->death = 1;
				print_status_unchecked("died", phi);
				return (pthread_mutex_unlock(&arg->status), 0);
			}
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

int	set_philo(int i, t_arg *args, t_philo **philos)
{
	t_philo	*new;

	new = ft_philonew(i, args);
	if (!new)
		return (0);
	if (pthread_create(&new->thread, NULL, start_routine, new))
		return (printf("%s %i %s\n", "Philosopher", i, "thread creation failed"), free(new), 0);
	ft_philoadd_back(philos, new);
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
	if (argc == 6 && args.numb_must_eat == 0)
		return (0);
	if (args.phil_numb == 1)
	{
		printf("%s0%s 1 is thinking\n", RED, NORMAL);
		printf("0 1 has taken a fork\n");
		usleep(args.time_to_die * 1000);
		printf("%u 1 died\n", args.time_to_die);
		return (0);
	}
	if (pthread_mutex_init(&args.status, NULL))
		return (printf("Mutex initialisation failed\n"), 0);
	pthread_mutex_lock(&args.status);
	i = 1;
	while (i <= args.phil_numb)
	{
		if (!set_philo(i, &args, &args.begin))
			return(printf("failed to iniate philosopher struct\n"), args.death = 1, pthread_mutex_unlock(&args.status), philo_clear(args.begin), pthread_mutex_destroy(&args.status), 0);
		i++;
	}
	args.start_time = get_time();
	pthread_mutex_unlock(&args.status);
	ft_time_lord(&args);
	philo_clear(args.begin);
	pthread_mutex_destroy(&args.status);
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
