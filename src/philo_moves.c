/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:40:47 by psoares           #+#    #+#             */
/*   Updated: 2021/11/23 18:07:17 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	if_dead(t_philo_o *arg, int i)
{
	if (arg->data->num_of_philo == 1 || (arg[i].philosofer.eating_st
			&& get_time() - arg[i].philosofer.eating_st
			> arg->data->time_to_die))
	{
		if (g_flag_dead == 0 && arg[i].philosofer.need_to_eat != 0)
		{
			g_flag_dead = 1;
			pthread_mutex_lock(arg->data->txt_mut);
			printf("%d ms %d died\n", get_time() - arg->data->time_st,
				arg[i].philosofer.philo_id + 1);
			pthread_mutex_unlock(arg->data->txt_mut);
		}
	}
}

void	death_check(t_philo_o *arg)
{
	int	i;

	i = 0;
	while (g_flag_dead == 0 && arg->data->fin_eat < arg->data->num_of_philo)
	{
		if (arg->data->num_of_philo == 1)
			if_dead(arg, i);
		else
		{
			if (i == arg->data->num_of_philo - 1)
				i = 0;
			if_dead(arg, i);
			i++;
		}
	}
}

void	philo_sleep_eat(int time)
{
	int	cur_time;
	int	res;

	cur_time = get_time();
	res = cur_time + time;
	while (cur_time < res && g_flag_dead == 0)
	{
		usleep(100);
		cur_time = get_time();
		if (g_flag_dead == 1)
			break ;
	}
}

void	sleeps(t_philo_o	*arg)
{
	if (g_flag_dead == 1)
		return ;
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d is sleeping\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	philo_sleep_eat(arg->data->time_to_sleep);
	if (g_flag_dead == 1)
		return ;
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d is thinking\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
}
