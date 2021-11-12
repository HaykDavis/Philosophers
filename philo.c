/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/12 16:18:33 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *eat(void *args)
{
	philo_o	*arg;

	arg = (philo_o *)args;
	while (1)
	{
		printf("Philo № %d started dinner\n", arg->philosofer->philo_number);
		pthread_mutex_lock(&forkk[arg->philosofer->left_fork]);
		pthread_mutex_lock(&forkk[arg->philosofer->right_fork]);
		printf("Philo № %d is eating %d %d\n", arg->philosofer->philo_number, arg->philosofer->left_fork, arg->philosofer->right_fork);
		sleep(1);
		pthread_mutex_unlock(&forkk[arg->philosofer->left_fork]);
		pthread_mutex_unlock(&forkk[arg->philosofer->right_fork]);
		printf("Philo № %d finished dinner\n", arg->philosofer->philo_number);
	}
	return NULL;
}


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
	philosopher->philo_number = philo_number;
    philosopher->left_fork = left_fork;
    philosopher->right_fork = right_fork;
}

int main(int argc, char **argv)
{
	int					i;
	int					z;
	pthread_t			trd[ft_atoi(argv[1])];
	philo_o				arguments[ft_atoi(argv[1])];
	
	arguments->philosofer = malloc(sizeof(philosopher_t) * ft_atoi(argv[1]));
	arguments->data = malloc(sizeof(philosopher_i) * ft_atoi(argv[1]));
	i = 0;
	while (i < ft_atoi(argv[1]))
		init_data(&arguments->data[i], argv), i++;
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_mutex_init(&(forkk[i]), NULL), i++;
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (i == ft_atoi(argv[1]) - 1)
			init_philosopher(&arguments->philosofer[i], i, i, 0);
		init_philosopher(&arguments->philosofer[i], i, i, i + 1), i++;
	}
	z = 0;
	while (z < ft_atoi(argv[1]))
        arguments[z].philosofer = &arguments->philosofer[z], z++;
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_create(&trd[i], NULL, eat, &arguments[i]), i++;
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_join(trd[i], NULL), i++;
	return (0);
}