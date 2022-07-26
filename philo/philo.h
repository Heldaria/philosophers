/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:41:45 by rigel             #+#    #+#             */
/*   Updated: 2022/07/26 21:51:09 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef NOCOLOR
#  define RED "\e[32m"
#  define NORMAL "\e[0m"
# else
#  define RED ""
#  define NORMAL ""
# endif

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_arg
{
	int				argc;
	uint32_t		phil_numb;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	uint32_t		numb_must_eat;
	uint64_t		start_time;
	pthread_mutex_t	status;
	bool			death;
	t_philo			*begin;
	pthread_t		time_lord;
}	t_arg;

typedef struct s_philo
{
	int				number;
	uint32_t		meal_count;
	uint64_t		last_meal;
	pthread_mutex_t	fork;
	pthread_t		thread;
	t_arg			*arg;
	struct s_philo	*next;
}	t_philo;

uint32_t		ft_ulong_atoi(const char *nptr);
t_philo			*ft_philonew(int i, t_arg *args);
uint64_t		get_time();
int				print_status(char *str, t_philo *philos);
void			*start_routine(void *philo);
int				ft_time_lord(t_arg *arg);
int				set_philo(int i, t_arg *args, t_philo **philos);
void			ft_philoadd_back(t_philo **alst, t_philo *new);
int				ft_sleep(t_philo *philo, uint64_t duration);
void			philo_clear(t_philo *philos);

#endif