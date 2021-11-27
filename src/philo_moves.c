/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:40:47 by psoares           #+#    #+#             */
/*   Updated: 2021/11/27 18:17:51 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	if_dead(t_philo_o *arg, int i)
{
	if (arg->data.num_of_philo == 1 || (arg->philosofer[i].eating_st
			&& get_time() - arg->philosofer[i].eating_st
			> arg->data.time_to_die))
	{
		if (arg->g_flag_dead == 0 && arg->philosofer[i].need_to_eat != 0)
		{
			arg->g_flag_dead = 1;
			pthread_mutex_lock(arg->txt_mut);
			printf("%d ms %d died\n", get_time() - arg->data.time_st,
				arg->philosofer[i].philo_id + 1);
		}
	}
}

void	death_check(t_philo_o *arg)
{
	int	i;

	i = 0;
	while (arg->g_flag_dead == 0 && arg->data.fin_eat < arg->data.num_of_philo)
	{
		if (arg->data.num_of_philo == 1)
			if_dead(arg, i);
		else
		{
			if (i == arg->data.num_of_philo - 1)
				i = 0;
			if_dead(arg, i);
			i++;
		}
	}
}

void	philo_sleep_eat(int time, t_philosopher	*arg)
{
	int	cur_time;
	int	res;

	cur_time = get_time();
	res = cur_time + time;
	while (cur_time < res && arg->obj->g_flag_dead == 0)
	{
		usleep(100);
		cur_time = get_time();
		if (arg->obj->g_flag_dead == 1)
			break ;
	}
}

void	sleeps(t_philosopher *arg)
{
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_detach(arg->obj->trd[arg->philo_id]);
		return ;
	}
	pthread_mutex_lock(arg->obj->txt_mut);
	printf("%d ms %d is sleeping\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	pthread_mutex_unlock(arg->obj->txt_mut);
	philo_sleep_eat(arg->datas->time_to_sleep, arg);
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_detach(arg->obj->trd[arg->philo_id]);
		return ;
	}
	pthread_mutex_lock(arg->obj->txt_mut);
	printf("%d ms %d is thinking\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	pthread_mutex_unlock(arg->obj->txt_mut);
}
