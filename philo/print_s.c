/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:27:46 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 15:28:15 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_s(t_list *philos, int status)
{
	int	index;

	index = philos->index;
	pthread_mutex_lock(philos->mprint);
	pthread_mutex_lock(&(philos->access));
	if (philos->dead && status != DEAD)
	{
		pthread_mutex_unlock(philos->mprint);
		pthread_mutex_unlock(&(philos->access));
		return ;
	}
	pthread_mutex_unlock(&(philos->access));
	if (status == TAKEF)
		printf("%ld %d has taken a fork\n", ft_ms(philos->starttime) - 15,
			index);
	else if (status == EAT)
		printf("%ld %d is eating\n", ft_ms(philos->starttime) - 15, index);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", ft_ms(philos->starttime) - 15, index);
	else if (status == THINK)
		printf("%ld %d is thinking\n", ft_ms(philos->starttime) - 15, index);
	else if (status == DEAD)
		printf("%ld %d died\n", ft_ms(philos->starttime) - 15, index);
	pthread_mutex_unlock(philos->mprint);
}

void	print_dead(t_list *philos, pthread_mutex_t *tempprint)
{
	int	index;

	index = philos->index;
	pthread_mutex_lock(tempprint);
	printf("%ld %d died\n", ft_ms(philos->starttime) - 15, index);
}
