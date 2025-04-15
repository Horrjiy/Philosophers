/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:51:45 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 14:04:19 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_now(void)
{
	long			ms;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000;
	ms += (now.tv_usec) / 1000;
	return (ms);
}

long	ft_ms(long starttime)
{
	return (ft_now() - starttime);
}

bool	ft_sleep(t_list *philos, long time_ms)
{
	long	start;

	start = ft_now();
	while (ft_now() - start < time_ms)
	{
		pthread_mutex_lock(&(philos->access));
		if (philos->dead == true)
			return (pthread_mutex_unlock(&(philos->access)), DEAD);
		pthread_mutex_unlock(&(philos->access));
		usleep(500);
	}
	return (true);
}
