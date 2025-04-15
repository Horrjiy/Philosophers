/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:27:46 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/14 16:19:24 by mpoplow          ###   ########.fr       */
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
		printf("%ldms %d has taken a fork\n", ft_ms(philos->starttime) - 15,
				index);
	else if (status == EAT)
		printf("%ldms %d is eating\n", ft_ms(philos->starttime) - 15, index);
	else if (status == SLEEP)
		printf("%ldms %d is sleeping\n", ft_ms(philos->starttime) - 15, index);
	else if (status == THINK)
		printf("%ldms %d is thinking\n", ft_ms(philos->starttime) - 15, index);
	else if (status == DEAD)
		printf("%ldms %d died\n", ft_ms(philos->starttime) - 15, index);
	pthread_mutex_unlock(philos->mprint);
}

void	print_lock(t_list *philos, char *str)
{
	pthread_mutex_lock(philos->mprint);
	printf("Ja: %s\n", str);
	pthread_mutex_unlock(philos->mprint);
}
