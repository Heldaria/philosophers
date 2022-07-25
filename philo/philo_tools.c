/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:43:26 by rigel             #+#    #+#             */
/*   Updated: 2022/07/25 12:21:44 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_philonew(int i, t_arg *args)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->number = i;
	new->last_meal = 0;
	new->meal_count = 0;
	if (pthread_mutex_init(&new->fork, NULL))
		return (printf("Mutex initialisation failed\n"), NULL);
	// if (pthread_create(&new->thread, NULL, start_routine, *philos))
	// 	return (printf("Thread creation failed\n"), NULL);
	new->arg = args;
	new->next = NULL;
	return (new);
}

void	ft_philoadd_back(t_philo **alst, t_philo *new)
{
	t_philo	*tmp;

	if (!alst || !new)
		return ;
	tmp = *alst;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
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