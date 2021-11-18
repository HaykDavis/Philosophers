/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:14:33 by psoares           #+#    #+#             */
/*   Updated: 2021/11/18 17:38:05 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_data(philosopher_i *data, char **argv) 
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
}


void init_philosopher(philosopher_t *philosopher,
						int philo_number,
                      unsigned left_fork,
                      unsigned right_fork) 
{
	philosopher->philo_id = philo_number;
    philosopher->left_fork = left_fork;
    philosopher->right_fork = right_fork;
}

void all_inits(philo_o	*arguments, char **argv)
{
	int	i;
	

	i = 0;
	flag_dead = 0;
	init_data(arguments->data, argv);
	arguments->data->time_st = get_time();
	while (i < ft_atoi(argv[1]))
	{
		arguments[i].data = arguments[0].data;
		pthread_mutex_init(&arguments->forkk[i], NULL);
		if (i == ft_atoi(argv[1]) - 1)
			init_philosopher(&arguments[i].philosofer, i, i, 0);
		init_philosopher(&arguments[i].philosofer, i, i, i + 1), i++;
	}
}
