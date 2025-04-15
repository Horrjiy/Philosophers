/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:23:31 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 17:46:56 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	grab_forks_odd(t_list *philos)
{
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == true)
		return (pthread_mutex_unlock(&(philos->access)), true);
	pthread_mutex_unlock(&(philos->access));
	if (philos->next == NULL)
		pthread_mutex_lock(&(philos->head->fork));
	else
		pthread_mutex_lock(&(philos->next->fork));
	print_s(philos, TAKEF);
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == true)
	{
		if (philos->next == NULL)
			pthread_mutex_unlock(&(philos->head->fork));
		else
			pthread_mutex_unlock(&(philos->next->fork));
		return (pthread_mutex_unlock(&(philos->access)), true);
	}
	pthread_mutex_unlock(&(philos->access));
	pthread_mutex_lock(&(philos->fork));
	print_s(philos, TAKEF);
	return (false);
}

static bool	grab_forks(t_list *philos)
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

static bool	eat_drop_fork(t_list *philos)
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

static bool	ft_routine_helper(t_list *philos)
{
	if (philos->index % 2 == 1)
	{
		if (grab_forks_odd(philos) == true || eat_drop_fork(philos) == true)
			return (false);
	}
	else
	{
		if (grab_forks(philos) == true || eat_drop_fork(philos) == true)
			return (false);
	}
	return (true);
}

void	*ft_threadroutine(void *vptr)
{
	t_list	*philos;

	philos = (t_list *)vptr;
	while (ft_ms(philos->starttime) < 15)
		usleep(100);
	if (philos->next == NULL && philos->index == 1)
		return (print_s(philos, 1), ft_sleep(philos, philos->time_eat), NULL);
	usleep((philos->index % 2) * 2000);
	while (1)
	{
		print_s(philos, THINK);
		pthread_mutex_lock(&(philos->access));
		if (philos->dead == true)
			return (pthread_mutex_unlock(&(philos->access)), NULL);
		pthread_mutex_unlock(&(philos->access));
		if (ft_routine_helper(philos) == false)
			return (NULL);
	}
	return (NULL);
}
