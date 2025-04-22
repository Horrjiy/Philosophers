/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validity.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:57:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/22 15:31:49 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

static int	ft_atoi(char *str)
{
	size_t	num;
	int		i;

	num = 0;
	i = num;
	while (str[i])
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	if (num > 2147483647)
		return (0);
	return ((int)num);
}

static void	valid_args_helper(int argc, char **argv, t_data *data)
{
	data->philnum = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eatnum = ft_atoi(argv[5]);
	else
		data->eatnum = -1;
	return ;
}

bool	ft_check_valid_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit_str(argv[i]))
			return (false);
		i++;
	}
	if (argc == 5 || argc == 6)
	{
		valid_args_helper(argc, argv, data);
		if (!data->philnum || !data->time_die || !data->time_eat
			|| !data->time_sleep || data->eatnum == 0)
			return (false);
	}
	else
		return (false);
	return (true);
}

void	ft_input_error(void)
{
	write(2, "Error: wrong input!\n", 20);
	write(2, "[1] number_of_philosophers\n", 27);
	write(2, "[2] time_to_die\n", 16);
	write(2, "[3] time_to_eat\n", 17);
	write(2, "[4] time_to_sleep\n", 18);
	write(2, "[optional] number_of_times_each_philosopher_must_eat\n", 53);
}
