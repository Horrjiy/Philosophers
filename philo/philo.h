/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:24:25 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/15 17:49:45 by mpoplow          ###   ########.fr       */
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

typedef enum e_status
{
	DEAD,
	TAKEF,
	EAT,
	SLEEP,
	THINK
}						t_status;

typedef struct s_data
{
	pthread_mutex_t		mprint;
	pthread_t			monitor;
	long				gettime;
	int					philnum;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					eatnum;
	struct s_list		*head;
}						t_data;

// -~--~--~--~- functions -~--~--~--~- //

void					ft_input_error(void);
bool					ft_check_valid_args(int argc, char **argv,
							t_data *data);

long					ft_ms(long starttime);
long					ft_now(void);
bool					ft_sleep(t_list *philos, long time_ms);

bool					ft_create_list(t_data *data, t_list **philos);
bool					ft_init_threads(t_data *data, t_list *philos);
void					*ft_threadroutine(void *vptr);
void					*ft_monitorroutine(void *vptr);
int						ft_deadcheck(t_list *philos,
							pthread_mutex_t *tempprint);

void					print_s(t_list *philos, int status);
void					print_dead(t_list *philos, pthread_mutex_t *tempprint);

// -~--~--~--~- list && list functions -~--~--~--~- //

struct					s_list
{
	pthread_t			thread;
	pthread_mutex_t		fork;
	pthread_mutex_t		access;
	pthread_mutex_t		*mprint;
	long				starttime;
	int					philnum;
	int					index;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					eatnum;
	long				last_meal;
	bool				dead;
	struct s_list		*next;
	struct s_list		*head;
};

t_list					*ft_init_node(int index, t_data *data);
int						ft_listlen(t_list *a);
t_list					*ft_lastnode(t_list *a);
void					free_list_simple(t_list **philos);
void					free_list(t_list **philos);
void					ft_node_addback(t_list **a, t_list *node);

#endif