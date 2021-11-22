/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:14:33 by psoares           #+#    #+#             */
/*   Updated: 2021/11/22 17:26:03 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_data(philosopher_i *data, char **argv, int argc) 
{
	data->number_of_philosophers = ft_atoi(argv[1]);
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


void init_philosopher(philo_o *philo,
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

void all_inits(philo_o	*arguments, char **argv, int argc)
{
	int	i;
	
	i = 0;
	flag_dead = 0;
	init_data(arguments->data, argv, argc);
	arguments->data->txt_mut = malloc(sizeof(pthread_mutex_t));
	while (i < ft_atoi(argv[1]))
	{
		arguments[i].data = arguments[0].data;
		pthread_mutex_init(&arguments->data->forkk[i], NULL);
		if (i == ft_atoi(argv[1]) - 1)
			init_philosopher(&arguments[i], i, i, 0);
		init_philosopher(&arguments[i], i, i, i + 1), i++;
	}
}
