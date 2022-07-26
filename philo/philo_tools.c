/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:43:26 by rigel             #+#    #+#             */
/*   Updated: 2022/07/26 21:48:15 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

void	ft_assert(bool condition, const char *message)
{
	(void)condition;
	(void)message;
}

t_philo	*ft_philonew(int i, t_arg *args)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->number = i;
	new->last_meal = get_time();
	new->meal_count = 0;
	if (pthread_mutex_init(&new->fork, NULL))
		return (printf("Mutex initialisation failed\n"), free(new), NULL);
	// if (pthread_create(&new->thread, NULL, start_routine, *philos))
	// 	return (printf("Thread creation failed\n"), NULL);
	new->arg = args;
	new->next = NULL;
	return (new);
}

void	ft_philoadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*tmp;

	ft_assert(alst, "alst est NULL");
	ft_assert(new, "new est NULL");
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = new;
			break ;
		}
		tmp = tmp->next;
	}
}

void	philo_clear(t_philo *philos)
{
	t_philo	*bis;
	t_philo	*tmp;

	bis = philos;
	while (bis)
	{
		pthread_join(bis->thread, NULL);
		bis = bis->next;
	}
	bis = philos;
	while (bis)
	{
		tmp = bis->next;
		pthread_mutex_destroy(&bis->fork);
		free(bis);
		bis = tmp;
	}
}