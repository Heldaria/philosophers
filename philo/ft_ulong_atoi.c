/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulong_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:55:05 by rigel             #+#    #+#             */
/*   Updated: 2022/07/28 12:45:56 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>

bool	ft_ulong_atoi(const char *nptr, uint32_t *res)
{
	int			i;
	uint32_t	result;

	i = 0;
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > (UINT32_MAX - (nptr[i] - '0') / 10))
			return (0);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	*res = result;
	return (1);
}
