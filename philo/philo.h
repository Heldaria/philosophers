/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 19:41:45 by rigel             #+#    #+#             */
/*   Updated: 2022/07/27 16:00:06 by llepiney         ###   ########.fr       */
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

/******************************MAIN*************************************/
uint32_t		ft_ulong_atoi(const char *nptr);
void			*start_routine(void *philo);
int				ft_time_lord(t_arg *arg);
void			*eating(t_philo *phi, pthread_mutex_t **first,
					pthread_mutex_t **second);

/*****************************MANAGE_TOOLS******************************/
void			print_status_unchecked(char *str, t_philo *philos);
int				print_status(char *str, t_philo *philos);
int				ft_sleep(t_philo *philo, uint64_t duration);
uint64_t		get_time(void);
int				set_philo_fail(t_arg *args);

/*****************************PHILO_TOOLS*******************************/
t_philo			*ft_philonew(int i, t_arg *args);
void			ft_philoadd_back(t_philo **alst, t_philo *new);
void			philo_clear(t_philo *philos);

/*****************************SET_TOOLS*********************************/
int				set_philo(int i, t_arg *args, t_philo **philos);
void			set_fork(t_philo *phi, pthread_mutex_t **first,
					pthread_mutex_t **second);
int				set_check_args(int argc, char **argv, t_arg *args);
int				solo_die(t_arg *args);

#endif
