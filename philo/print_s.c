/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:27:46 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/10 13:34:00 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_s(t_list *philos, int status)
{
	long	time;
	int		index;

	index = philos->index;
	pthread_mutex_lock(philos->mprint);
	time = ft_ms(philos->starttime) - 10;
	if (status == TAKEF)
		printf("%ldms %d has taken a fork\n", time, index);
	else if (status == EAT)
		printf("%ldms %d is eating\n", time, index);
	else if (status == SLEEP)
		printf("%ldms %d is sleeping\n", time, index);
	else if (status == THINK)
		printf("%ldms %d is thinking\n", time, index);
	else if (status == DEAD)
		printf("%ldms %d died\n", time, index);
	pthread_mutex_unlock(philos->mprint);
}
