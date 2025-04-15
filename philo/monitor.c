/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:11:17 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 15:59:11 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_all(t_list *philos, pthread_mutex_t *tempprint)
{
	while (philos)
	{
		pthread_mutex_lock(&(philos->access));
		philos->dead = true;
		pthread_mutex_unlock(&(philos->access));
		philos = philos->next;
	}
	pthread_mutex_unlock(tempprint);
}

bool	all_eaten_up(t_list *philos, pthread_mutex_t *tempprint)
{
	t_list	*temp;

	temp = philos->head;
	while (temp)
	{
		pthread_mutex_lock(&(temp->access));
		if (temp->eatnum != 0)
		{
			pthread_mutex_unlock(&(temp->access));
			return (false);
		}
		pthread_mutex_unlock(&(temp->access));
		temp = temp->next;
	}
	return (pthread_mutex_lock(tempprint), true);
}

int	ft_deadcheck(t_list *philos, pthread_mutex_t *tempprint)
{
	t_list	*temp;

	temp = philos->head;
	while (temp)
	{
		pthread_mutex_lock(&(temp->access));
		if ((ft_now() - temp->last_meal) > temp->time_die)
		{
			temp->dead = true;
			pthread_mutex_unlock(&(temp->access));
			print_dead(temp, tempprint);
			return (DEAD);
		}
		pthread_mutex_unlock(&(temp->access));
		temp = temp->next;
	}
	return (1);
}

void	*ft_monitorroutine(void *vptr)
{
	t_list			*philos;
	pthread_mutex_t	*tempprint;

	philos = (t_list *)vptr;
	tempprint = philos->mprint;
	while (ft_ms(philos->starttime) < 30)
		usleep(100);
	while (1)
	{
		usleep(1000);
		if (ft_deadcheck(philos, tempprint) == DEAD)
			return (ft_kill_all(philos, tempprint), NULL);
		if (all_eaten_up(philos, tempprint) == true)
			return (ft_kill_all(philos, tempprint), NULL);
	}
}
