/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:45:16 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/28 13:25:29 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_num(int argc, char **argv, int i)
{
	int	end;
	int	j;

	if (argc == 6)
		end = 5;
	else
		end = 4;
	while (i <= end)
	{
		j = 0;
		if (argv[i][j] == '\0')
			return (0);
		while (argv[i][j])
		{
			if (argv[i][0] == '-')
				return (0);
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

bool	int_check(char **argv, t_arg *args)
{
	if (!ft_ulong_atoi(argv[1], &args->phil_numb)
		|| !ft_ulong_atoi(argv[2], &args->time_to_die)
		|| !ft_ulong_atoi(argv[3], &args->time_to_eat)
		|| !ft_ulong_atoi(argv[4], &args->time_to_sleep)
		|| (args->argc == 6 && !ft_ulong_atoi(argv[5], &args->numb_must_eat)))
		return (0);
	return (1);
}
