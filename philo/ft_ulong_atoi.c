/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulong_atoi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 23:55:05 by rigel             #+#    #+#             */
/*   Updated: 2022/07/27 16:01:51 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint32_t	ft_ulong_atoi(const char *nptr)
{
	int			i;
	uint32_t	result;

	i = 0;
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result);
}
