/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:17:03 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/09 20:10:53 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_create_list(t_data *data, t_list **philos)
{
	int		i;
	t_list	*temp;
	
	if (pthread_mutex_init(&data->mprint, NULL) != 0)
	return (false);
	data->head = NULL;
	*philos = ft_init_node(1, data);
	i = 2;
	data->head = *philos;
	while (i <= data->philnum + 1)
	{
		temp = ft_init_node(i, data);
		if (!temp)
			return (false);
		ft_node_addback(philos, temp);
		i++;
	}
	return (true);
}

bool	ft_init_threads(t_list *philos)
{
	t_list	*temp;
	pthread_t monitor;

	temp = philos;
	while (temp->next)
	{
		if (pthread_create(&temp->thread, NULL, ft_threadroutine, temp) != 0)
			return (free_list(&philos), false);
		temp = temp->next;
	}
	if (pthread_create(&monitor, NULL, ft_monitorroutine, philos) != 0)
			return (free_list(&philos), false);
	return (true);
}
