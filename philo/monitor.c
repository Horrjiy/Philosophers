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

void	*ft_monitorroutine(void *vptr)
{
	t_list	*philos;

	philos = (t_list *)vptr;
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
		if (philos->next)
			philos = philos->next;
		else
			philos = philos->head;
	}
}
