/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:41:45 by rigel             #+#    #+#             */
/*   Updated: 2022/07/22 20:07:33 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_arg
{
	int				argc;
	uint32_t		phil_numb;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		numb_must_eat;
	uint64_t		time_passed;
	pthread_mutex_t	start_all;
	pthread_mutex_t	status;
	bool			death;
	pthread_t		time_lord;
}	t_arg;

typedef struct s_philo
{
	int				number;
	uint32_t		meal_count;
	uint32_t		last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
	t_arg			*arg;
	struct s_philo	*next;
}	t_philo;

uint32_t	ft_ulong_atoi(const char *nptr);
t_philo			*ft_philonew(int i, t_arg *args, t_philo **philos);
uint64_t		get_time();
void			print_status(char *str, t_philo *philos);
void			*start_routine(void *philo);
void			*ft_time_lord(void *philo);
int				set_philo(int i, t_arg *args, t_philo **philos);
void			ft_philoadd_back(t_philo **alst, t_philo *new);

#endif