/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:14:33 by psoares           #+#    #+#             */
/*   Updated: 2021/11/29 14:31:39 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_data(t_philo *data, char **argv, int argc)
{
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->fin_eat = 0;
	data->time_st = 0;
	if (argc < 6)
	{
		data->must_to_eat = -1;
		return ;
	}
	data->must_to_eat = ft_atoi(argv[5]);
}

void	init_philosopher(t_philo_o *arg,
						int id,
						unsigned left_fork,
						unsigned right_fork)
{
	arg->philosofer[id].philo_id = id;
	arg->philosofer[id].eating_st = 0;
	arg->philosofer[id].sleeping_st = 0;
	arg->philosofer[id].left_fork = left_fork;
	arg->philosofer[id].right_fork = right_fork;
	arg->philosofer[id].need_to_eat = arg->data.must_to_eat;
	arg->philosofer[id].datas = &arg->data;
	arg->philosofer[id].obj = arg;
}

void	malloc_data(t_philo_o	*arg, char **argv)
{
	arg->txt_mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!arg->txt_mut)
	{
		free(arg);
		return ;
	}
	arg->forkk = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(argv[1]));
	if (!arg->forkk)
	{
		free(arg->txt_mut);
		free(arg);
		return ;
	}
	arg->philosofer = (t_philosopher *)malloc(sizeof(t_philosopher)
			* ft_atoi(argv[1]));
	if (!arg->philosofer)
	{
		free(arg->forkk);
		free(arg->txt_mut);
		free(arg);
		return ;
	}
}

void	all_inits(t_philo_o	*arg, char **argv, int argc)
{
	int	i;

	i = 0;
	arg->g_flag_dead = 0;
	init_data(&arg->data, argv, argc);
	malloc_data(arg, argv);
	pthread_mutex_init(arg->txt_mut, NULL);
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&arg->forkk[i], NULL);
		if (i == ft_atoi(argv[1]) - 1)
			init_philosopher(arg, i, i, 0);
		else
			init_philosopher(arg, i, i, i + 1);
		i++;
	}
}
