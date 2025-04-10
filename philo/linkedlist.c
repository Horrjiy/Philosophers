/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:31:58 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/09 20:28:37 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_list	*ft_init_node(int index, t_data *data)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	if (pthread_mutex_init(&node->fork, NULL) != 0)
		return (free(node), NULL);
	node->next = NULL;
	node->thread = NULL;
	node->dead = false;
	node->philnum = data->philnum;
	node->index = index;
	node->starttime = data->gettime;
	node->time_die = data->time_die;
	node->time_eat = data->time_eat;
	node->time_sleep = node->time_sleep;
	node->eatnum = data->eatnum;
	node->mprint = &(data->mprint);
	if (data->head)
		node->head = data->head;
	else
		node->head = node;
	return (node);
}

//returns the length of the linked list
int	ft_listlen(t_list *a)
{
	t_list	*temp;
	int		i;

	if (!a)
		return (0);
	temp = a;
	i = 1;
	while (temp->next != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

//returns the last node of the linked list
t_list	*ft_lastnode(t_list *a)
{
	t_list	*temp;

	temp = a;
	if (!temp)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	free_list(t_list **philos)
{
	t_list	*temp;

	if (!philos || !(*philos))
		return ;
	if ((*philos)->mprint)
		pthread_mutex_destroy((*philos)->mprint);
	while (*philos)
	{
		temp = (*philos)->next;
		if ((*philos)->thread != NULL)
			pthread_join((*philos)->thread, NULL);
		pthread_mutex_destroy(&((*philos)->fork));
		free(*philos);
		*philos = temp;
	}
}

void	ft_node_addback(t_list **a, t_list *node)
{
	t_list	*temp;

	if (!node)
		return ;
	if (!a)
	{
		*a = node;
		return ;
	}
	else
	{
		temp = ft_lastnode(*a);
		temp->next = node;
	}
}
