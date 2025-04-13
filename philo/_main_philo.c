/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:22:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/07 16:51:32 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data			data;
	t_list			*philos;

	if (!ft_check_valid_args(argc, argv, &data))
		return (ft_input_error(), 1);
	data.gettime = ft_now();
	if (!ft_create_list(&data, &philos))
		return (free_list(&philos), 12);
	if (!ft_init_threads(&data, philos))
		return (free_list(&philos), 2);
	free_list(&philos);
	pthread_join(data.monitor, NULL);
	return (0);
}
