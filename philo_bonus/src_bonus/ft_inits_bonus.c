/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inits_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:14:33 by psoares           #+#    #+#             */
/*   Updated: 2021/11/29 13:01:46 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_forks(t_philo_o *data)
{
	sem_unlink("/forks");
	data->forkk = sem_open("/forks", O_CREAT, S_IRWXU, data->data.num_of_philo);
	if (data->forkk == SEM_FAILED)
		return (1);
	sem_unlink("/print_lock");
	data->txt_mut = sem_open("/print_lock", O_CREAT, S_IRWXU, 1);
	if (data->txt_mut == SEM_FAILED)
		return (1);
	return (0);
}

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

void	init_philosopher(t_philo_o *arg, int id)
{
	arg->philosofer[id].philo_id = id;
	arg->philosofer[id].eating_st = 0;
	arg->philosofer[id].sleeping_st = 0;
	arg->philosofer[id].need_to_eat = arg->data.must_to_eat;
	arg->philosofer[id].datas = &arg->data;
	arg->philosofer[id].obj = arg;
}

void	malloc_data(t_philo_o	*arg, char **argv)
{
	arg->philosofer = (t_philosopher *)malloc(sizeof(t_philosopher)
			* ft_atoi(argv[1]));
	if (!arg->philosofer)
	{
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
	init_forks(arg);
	while (i < ft_atoi(argv[1]))
	{
		init_philosopher(arg, i);
		i++;
	}
}
