/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:23:31 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/10 13:43:51 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_list *philos, bool side)
{
		if (side == LEFT)
		{
			pthread_mutex_lock(&(philos->fork));
			print_s(philos, TAKEF);
		}
		else if (side == RIGHT)
		{
			if (philos->next == NULL)
				pthread_mutex_lock(&(philos->head->fork));
			else
				pthread_mutex_lock(&(philos->next->fork));
			print_s(philos, TAKEF);
		}
}

void	eat_drop_fork(t_list *philos)
{
	if (!philos->dead)
	{
		print_s(philos, EAT);
		usleep(philos->time_eat * 1000);
	}
	pthread_mutex_unlock(&(philos->fork));
	if (philos->next == NULL)
		pthread_mutex_unlock(&(philos->head->fork));
	else
		pthread_mutex_unlock(&(philos->next->fork));
	if (!philos->dead)
	{
		print_s(philos, SLEEP);
		usleep(philos->time_sleep * 1000);
	}
}

int	ft_deadcheck(t_list *philos)
{
	if (philos->dead == true)
		return (0);
	if ((ft_now() - philos->last_meal) > philos->time_die)
	{
		philos->dead = true;
		return (0);
	}
	return (1);
}

void	*ft_threadroutine(void *vptr)
{
	t_list	*philos;
	int		i;

	philos = (t_list *)vptr;
	while (ft_ms(philos->starttime) < 10)
		usleep(100);
	i = 0;
	while (1)
	{
		if (ft_deadcheck(philos) == DEAD)
			return (print_s(philos, DEAD), NULL);
		if (philos->index % 2 == i)
		{
			grab_fork(philos, LEFT);
			grab_fork(philos, RIGHT);
			eat_drop_fork(philos);
			if (ft_deadcheck(philos) == DEAD)
				return (NULL);
		}
		else
			print_s(philos, THINK);
		i = !i;
	}
	return (NULL);
}
