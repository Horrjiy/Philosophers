/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:51:45 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/10 10:35:42 by mpoplow          ###   ########.fr       */
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
	return (ft_now() - starttime);
}

