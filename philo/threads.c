/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:23:31 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 11:52:54 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	grab_forks(t_list *philos)
{
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == true)
		return (pthread_mutex_unlock(&(philos->access)), true);
	pthread_mutex_unlock(&(philos->access));
	pthread_mutex_lock(&(philos->fork));
	print_s(philos, TAKEF);
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == true)
	{
		pthread_mutex_unlock(&(philos->fork));
		return (pthread_mutex_unlock(&(philos->access)), true);
	}
	pthread_mutex_unlock(&(philos->access));
	if (philos->next == NULL)
		pthread_mutex_lock(&(philos->head->fork));
	else
		pthread_mutex_lock(&(philos->next->fork));
	print_s(philos, TAKEF);
	return (false);
}

bool	eat_drop_fork(t_list *philos)
{
	print_s(philos, EAT);
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == false)
	{
		philos->last_meal = ft_now();
		if (philos->eatnum > 0)
			philos->eatnum--;
	}
	pthread_mutex_unlock(&(philos->access));
	ft_sleep(philos, philos->time_eat);
	pthread_mutex_unlock(&(philos->fork));
	if (philos->next == NULL)
		pthread_mutex_unlock(&(philos->head->fork));
	else
		pthread_mutex_unlock(&(philos->next->fork));
	print_s(philos, SLEEP);
	if (ft_sleep(philos, philos->time_sleep) == DEAD)
		return (true);
	return (false);
}

void	*ft_threadroutine(void *vptr)
{
	t_list	*philos;
	int		i;

	philos = (t_list *)vptr;
	while (ft_ms(philos->starttime) < 15)
		usleep(100);
	usleep((philos->index % 2) * 500);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(philos->access));
		if (philos->dead == true)
			return (pthread_mutex_unlock(&(philos->access)), NULL);
		pthread_mutex_unlock(&(philos->access));
		if (philos->index % 2 == i)
		{
			if (grab_forks(philos) == true || eat_drop_fork(philos) == true)
				return (NULL);
		}
		else
			print_s(philos, THINK);
		i = !i;
	}
	return (NULL);
}
