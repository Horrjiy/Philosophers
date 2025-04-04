/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:22:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/04 18:56:53 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// debug:
// #include <stdlib.h>

bool	ft_create_threads(t_data *data, t_list **philos)
{
	int	i;
	t_list *temp;

	*philos = ft_init_node(1, data);
	i = 2;
	while(i <= data->philnum)
	{
		temp = ft_init_node(i, data);
		if(!temp)
			return(false);
		ft_node_addback(philos, temp);
		i++;
	}
	return(true);
}

void free_list(t_list **philos)
{
	t_list	*temp;

	while (*philos)
	{
		temp = (*philos)->next;
		free(*philos);
		*philos = temp;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_list	*philos;

	if (ft_check_valid_args(argc, argv, &data) == false)
		return (ft_input_error(), 1);
	gettimeofday(&data.starttime, NULL);
	if (!ft_create_threads(&data, &philos))
		return (free_list(&philos), 2);
	return (free_list(&philos),0);
}
