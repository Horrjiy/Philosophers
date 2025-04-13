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

bool	grab_forks(t_list *philos)
{
	pthread_mutex_lock(&(philos->access));
	if (philos->dead == true)
		return(pthread_mutex_unlock(&(philos->access)), true);
	pthread_mutex_lock(&(philos->fork));
	if (!philos->dead)
		print_s(philos, TAKEF);
	while(philos->index == 1 && philos->next == NULL && !philos->dead)
		usleep(100);
	if (philos->next == NULL)
		pthread_mutex_lock(&(philos->head->fork));
	else
		pthread_mutex_lock(&(philos->next->fork));
	if (!philos->dead)
		print_s(philos, TAKEF);
	return(pthread_mutex_unlock(&(philos->access)), false);
}

void	eat_drop_fork(t_list *philos)
{
	pthread_mutex_lock(&(philos->access));
	if (!philos->dead)
	{
		print_s(philos, EAT);
		philos->last_meal = ft_now();
		usleep(philos->time_eat * 1000);
		if(philos->eatnum > 0)
			philos->eatnum--;
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
	pthread_mutex_unlock(&(philos->access));
}



void	*ft_threadroutine(void *vptr)
{
	t_list	*philos;
	int		i;
	philos = (t_list *)vptr;
	printf("fritt\n");
	while (ft_ms(philos->starttime) < 15)
		usleep(100);
	i = 0;
	usleep((philos->index % 2) * 500);
	while (1)
	{
		if (philos->index % 2 == i)
		{
			philos->dead = grab_forks(philos);	
			if(philos->dead == true)
				return(NULL);
			eat_drop_fork(philos);
		}
		else
			print_s(philos, THINK);
		i = !i;
	}
	return (NULL);
}
