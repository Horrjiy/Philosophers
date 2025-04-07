/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:17:03 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/07 15:35:42 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_create_list(t_data *data, t_list **philos)
{
	int		i;
	t_list	*temp;

	*philos = ft_init_node(1, data);
	i = 2;
	while (i <= data->philnum)
	{
		temp = ft_init_node(i, data);
		if (!temp)
			return (false);
		ft_node_addback(philos, temp);
		i++;
	}
	return (true);
}

bool	ft_init_threads(t_data *data, t_list *philos)
{
	t_list	*temp;

	(void)data;
	temp = philos;
	while (philos->next)
	{
		if (!pthread_create(&temp->thread, NULL, ft_threadroutine, temp))
			return (free_list(&philos), false);
		temp = temp->next;
	}
	return (true);
}
