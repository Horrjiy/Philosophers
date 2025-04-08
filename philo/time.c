/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:51:45 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/08 15:03:25 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_now(void)
{
	long			ms;
	struct timeval	now;

	gettimeofday(&now, NULL);
	ms = (now.tv_sec) * 1000;
	ms += (now.tv_usec) / 1000;
	return (ms);
}

long	ft_ms(long starttime)
{
	long	now;

	now = ft_now();
	return (now - starttime);
}
