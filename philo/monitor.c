/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:11:17 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 12:10:50 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_all(t_list *philos)
{
	pthread_mutex_t	*tempprint;

	tempprint = philos->head->mprint;
	pthread_mutex_lock(tempprint);
	while (philos)
	{
		pthread_mutex_lock(&(philos->access));
		philos->dead = true;
		pthread_mutex_unlock(&(philos->access));
		philos = philos->next;
	}
	pthread_mutex_unlock(tempprint);
}

bool	all_eaten_up(t_list *philos)
{
	t_list	*temp;

	temp = philos->head;
	while (temp)
	{
		pthread_mutex_lock(&(temp->access));
		if (temp->eatnum != 0)
			return (pthread_mutex_unlock(&(temp->access)), false);
		pthread_mutex_unlock(&(temp->access));
		temp = temp->next;
	}
	return (true);
}

int	ft_deadcheck(t_list *philos)
{
	t_list	*temp;

	temp = philos->head;
	while (temp)
	{
		pthread_mutex_lock(&(temp->access));
		if ((ft_now() - temp->last_meal) >= temp->time_die)
		{
			temp->dead = true;
			pthread_mutex_unlock(&(temp->access));
			return (print_s(temp, DEAD), DEAD);
		}
		pthread_mutex_unlock(&(temp->access));
		temp = temp->next;
	}
	return (1);
}

void	*ft_monitorroutine(void *vptr)
{
	t_list	*philos;

	philos = (t_list *)vptr;
	while (1)
	{
		usleep(1000);
		if (ft_deadcheck(philos) == DEAD)
			return (ft_kill_all(philos), NULL);
		if (all_eaten_up(philos) == true)
			return (ft_kill_all(philos), NULL);
	}
}

// void	ft_kill_all(t_list *philos)
// {
// 	while (philos)
// {
// 		pthread_mutex_lock(&(philos->access));
// 		philos->dead = true;
// 		pthread_mutex_unlock(&(philos->access));
// 		philos = philos->next;
// }
// }

// bool	all_eaten_up(t_list *head)
// {
// 	t_list	*temp;

// 	temp = head;
// 	while (temp)
// 	{
// 		pthread_mutex_lock(&(temp->access));
// 		if (temp->eatnum != 0)
// 			return (pthread_mutex_unlock(&(temp->access)), false);
// 		pthread_mutex_unlock(&(temp->access));
// 		temp = temp->next;
// 	}
// 	return (true);
// }

// int	ft_deadcheck(t_list *philos)
// {
// 	if (philos->dead == true)
// 		return (0);
// 	if ((ft_now() - philos->last_meal) > philos->time_die)
// 	{
// 		philos->dead = true;
// 		return (0);
// 	}
// 	return (1);
// }

// void	*ft_monitorroutine(void *vptr)
// {
// 	t_list	*philos;

// 	philos = (t_list *)vptr;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&(philos->access));
// 		if (ft_deadcheck(philos) == DEAD)
// 			print_s(philos, DEAD);
// 		if (philos->dead == true)
// 			return (pthread_mutex_unlock(&(philos->access)),
// 					ft_kill_all(philos->head),
// 					NULL);
// 		pthread_mutex_unlock(&(philos->access));
// 		if (all_eaten_up(philos->head) == true)
// 		{
// 			ft_kill_all(philos->head);
// 			return (NULL);
// 		}
// 		if (philos->next)
// 			philos = philos->next;
// 		else
// 			philos = philos->head;
// 	}
// }
