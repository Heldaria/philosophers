/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:31:36 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/28 16:28:59 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	set_fork(t_philo *phi, pthread_mutex_t **first,
			pthread_mutex_t **second)
{
	if (phi->number % 2)
	{
		*first = &phi->fork;
		if (phi->next == NULL)
			*second = &phi->arg->begin->fork;
		else
			*second = &phi->next->fork;
	}
	else
	{
		*second = &phi->fork;
		if (phi->next == NULL)
			*first = &phi->arg->begin->fork;
		else
			*first = &phi->next->fork;
	}
}

int	set_philo(int i, t_arg *args, t_philo **philos)
{
	t_philo	*new;

	new = ft_philonew(i, args);
	if (!new)
		return (0);
	if (pthread_create(&new->thread, NULL, start_routine, new))
		return (printf("%s %i %s\n", "Philosopher", i,
				"thread creation failed"), free(new), 0);
	ft_philoadd_back(philos, new);
	return (1);
}

int	set_check_args(int argc, char **argv, t_arg *args)
{
	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments\n"), 0);
	if (!is_num(argc, argv, 1))
		return (printf("At least one arg is not a positive int\n"), 0);
	args->phil_numb = ft_atoi(argv[1]);
	if (args->phil_numb <= 0)
		return (printf("Invalid number of philosopher(s)\n"), 0);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->argc = argc;
	args->death = 0;
	args->begin = NULL;
	if (argc == 6)
		args->numb_must_eat = ft_atoi(argv[5]);
	else
		args->numb_must_eat = 0;
	if (!int_check(argv, args))
		return (printf("At least one arg leads to int overflow\n"), 0);
	if (argc == 6 && args->numb_must_eat == 0)
		return (0);
	return (1);
}

int	solo_die(t_arg *args)
{
	if (args->phil_numb == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 has taken a fork\n");
		usleep(args->time_to_die * 1000);
		printf("%lld 1 died\n", args->time_to_die);
		return (0);
	}
	return (1);
}
