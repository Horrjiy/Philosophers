/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:22:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/02 18:26:10 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// debug:
#include <stdlib.h>

void *stuff(void *vptr)
{
	printf("Num: %d\n", (*((int*)vptr) * *((int*)vptr)));
	return(NULL);
}

void kek(char *k)
{
	int num;
	num = atoi(k);
	pthread_t thread1;
	pthread_create(&thread1, NULL, stuff, (void*)&num);
}

int	main(int argc, char *argv[])
{
	struct timeval time;
	(void)argc;
	int i = 0;
	
	while(i < 3) 
	{
	kek(argv[i]);
	i++;
	}

	gettimeofday(&time, 0);

	// pthread_join(thread1, NULL);
}
