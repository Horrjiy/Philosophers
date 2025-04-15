/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:22:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 16:21:05 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_list_simple(t_list **philos)
{
	t_list	*temp;

	if (!philos || !(*philos))
		return ;
	while (*philos)
	{
		temp = (*philos)->next;
		pthread_mutex_destroy(&((*philos)->fork));
		pthread_mutex_destroy(&((*philos)->access));
		free(*philos);
		*philos = temp;
	}
}

void	free_list(t_list **philos)
{
	t_list			*temp;
	pthread_mutex_t	*tempprint;

	tempprint = (*philos)->mprint;
	if (!philos || !(*philos))
		return ;
	temp = *philos;
	while (temp)
	{
		if (temp->thread != 0)
			pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
	while(*philos)
	{
		temp = (*philos)->next;
		pthread_mutex_destroy(&((*philos)->fork));
		pthread_mutex_destroy(&((*philos)->access));
		free(*philos);
		*philos = temp;
	}
	pthread_mutex_lock(tempprint);
	pthread_mutex_unlock(tempprint);
	pthread_mutex_destroy(tempprint);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_list	*philos;

	if (!ft_check_valid_args(argc, argv, &data))
		return (ft_input_error(), 1);
	data.gettime = ft_now();
	if (!ft_create_list(&data, &philos))
		return (free_list_simple(&philos), 12);
	if (!ft_init_threads(&data, philos))
		return (free_list(&philos), 2);
	pthread_join(data.monitor, NULL);
	free_list(&philos);
	return (0);
}
