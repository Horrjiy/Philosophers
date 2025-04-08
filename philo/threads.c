/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:23:31 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/08 18:55:53 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_list *philos, bool side)
{
	if (side == LEFT)
	{
		pthread_mutex_lock(&(philos->fork));
		print_s(philos, philos->index, TAKEF);
	}
	else if (side == RIGHT)
	{
		if (philos->next == NULL)
			pthread_mutex_lock(&(philos->head->fork));
		else
			pthread_mutex_lock(&(philos->next->fork));
		print_s(philos, philos->index, TAKEF);
	}
}

void	*ft_threadroutine(void *vptr)
{
	t_list	*philos;

	philos = (t_list *)vptr;
	while (ft_ms(philos->starttime) < 10)
		usleep(100);
	while (1)
	{
		if (philos->index % 2 == 0)
		{
			grab_fork(philos, LEFT);
			grab_fork(philos, RIGHT);
		}
		
	}
	return (NULL);
}
