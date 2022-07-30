/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 11:45:16 by llepiney          #+#    #+#             */
/*   Updated: 2022/07/30 12:02:48 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

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

static int	is_int(char *n)
{
	int	i;

	if (!n)
		return (0);
	if (ft_atoi(n) < 0 || ft_atoi(n) > 2147483647)
		return (-1);
	i = 0;
	if (n[i] == '-')
		i++;
	while (n[i])
	{
		if (n[i] < '0' || n[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

bool	int_check(char **argv, t_arg *args)
{
	(void)argv;
	if (is_int(argv[1]) < 0
		|| is_int(argv[2]) < 0
		|| is_int(argv[3]) < 0
		|| is_int(argv[4]) < 0
		|| (args->argc == 6 && is_int(argv[5]) < 0))
		return (0);
	return (1);
}
