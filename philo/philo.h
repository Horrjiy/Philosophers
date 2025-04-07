/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:24:25 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/07 15:34:01 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_list	t_list;

typedef struct s_data
{
	struct timeval		gettime;
	int					philnum;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					eatnum;
}						t_data;

long					ft_ms(struct timeval starttime);
void					ft_input_error(void);
bool					ft_check_valid_args(int argc, char **argv,
							t_data *data);
bool					ft_create_list(t_data *data, t_list **philos);
void					*ft_threadroutine(void *vptr);
bool					ft_init_threads(t_data *data, t_list *philos);

// -~--~--~--~- list -~--~--~--~- //

struct					s_list
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	long				starttime;
	int					index;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	struct s_list		*next;
};

t_list					*ft_init_node(int index, t_data *data);
int						ft_listlen(t_list *a);
t_list					*ft_lastnode(t_list *a);
void					free_list(t_list **philos);
void					ft_node_addback(t_list **a, t_list *node);

#endif