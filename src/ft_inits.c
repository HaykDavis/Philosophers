/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:14:33 by psoares           #+#    #+#             */
/*   Updated: 2021/11/22 19:36:21 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_data(t_philo *data, char **argv, int argc)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc < 6)
	{
		data->must_to_eat = -1;
		return ;
	}
	data->must_to_eat = ft_atoi(argv[5]);
	data->fin_eat = 0;
}

void	init_philosopher(t_philo_o *philo,
						int philo_number,
					  unsigned left_fork,
					  unsigned right_fork)
{
	philo->philosofer.philo_id = philo_number;
	philo->philosofer.left_fork = left_fork;
	philo->philosofer.right_fork = right_fork;
	philo->philosofer.eating_st = 0;
	philo->philosofer.need_to_eat = philo->data->must_to_eat;
}

void	all_inits(t_philo_o	*arg, char **argv, int argc)
{
	int	i;

	i = 0;
	g_flag_dead = 0;
	init_data(arg->data, argv, argc);
	arg->data->txt_mut = malloc(sizeof(pthread_mutex_t));
	while (i < ft_atoi(argv[1]))
	{
		arg[i].data = arg[0].data;
		pthread_mutex_init(&arg->data->forkk[i], NULL);
		if (i == ft_atoi(argv[1]) - 1)
			init_philosopher(&arg[i], i, i, 0);
		init_philosopher(&arg[i], i, i, i + 1), i++;
	}
}
