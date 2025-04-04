/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:24:25 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/04 18:58:00 by mpoplow          ###   ########.fr       */
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

typedef struct s_data
{
	struct timeval	starttime;
	int				philnum;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				eatnum;
}					t_data;

void				ft_input_error(void);
bool				ft_check_valid_args(int argc, char **argv, t_data *data);

// -~--~--~--~- list -~--~--~--~- //

typedef struct s_list
{
	pthread_t		thread;
	pthread_mutex_t fork;
	struct timeval	starttime;
	int				index;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	struct s_list	*next;
}					t_list;

t_list				*ft_init_node(int index, t_data *data);
int					ft_listlen(t_list *a);
t_list				*ft_lastnode(t_list *a);
t_list				*ft_secondlastnode(t_list *a);
void				ft_node_addback(t_list **a, t_list *node);

#endif