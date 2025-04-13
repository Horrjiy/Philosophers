/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:11:17 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/10 13:40:19 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_all(t_list *philos)
{
	while (philos->next)
	{
		philos->dead = true;
		philos = philos->next;
	}
	philos->dead = true;
}

bool all_eaten_up(t_list *head)
{
	t_list *temp;
	temp = head;
	while(temp)
	{
		if(temp->eatnum != 0)
			return(false);
		temp = temp->next;
	}
	return (true);
}

int	ft_deadcheck(t_list *philos)
{
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == true)
		return (pthread_mutex_unlock(&(philos->access)), 0);
	if ((ft_now() - philos->last_meal) > philos->time_die)
	{
		philos->dead = true;
		return (pthread_mutex_unlock(&(philos->access)), 0);
	}
	return (pthread_mutex_unlock(&(philos->access)), 1);
}

void	*ft_monitorroutine(void *vptr)
{
	t_list	*philos	;

	philos = (t_list *)vptr;
	printf("frutt\n");
	while (1)
	{
		if (ft_deadcheck(philos) == DEAD)
		{
			print_s(philos, DEAD);
			philos->dead = true;
		}
		if (philos->dead == true)
		{
			ft_kill_all(philos->head);
			return (NULL);
		}
		if(all_eaten_up(philos->head) == true)
		{
			ft_kill_all(philos->head);
			return(NULL);
		}
		if (philos->next)
			philos = philos->next;
		else
			philos = philos->head;
	}
}
