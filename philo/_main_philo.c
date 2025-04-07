/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:22:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/07 15:37:59 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_ms(struct timeval starttime)
{
	long			ms;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec - starttime.tv_sec) * 1000;
	ms += (now.tv_usec - starttime.tv_usec) / 1000;
	return (ms);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_list	*philos;

	if (!ft_check_valid_args(argc, argv, &data))
		return (ft_input_error(), 1);
	gettimeofday(&data.gettime, NULL);
	if (!ft_create_list(&data, &philos))
		return (free_list(&philos), 12);
	if (!ft_init_threads(&data, philos))
		return (free_list(&philos), 12);
	// continue
	// * * * //
	// end
	return (free_list(&philos), 0);
}
