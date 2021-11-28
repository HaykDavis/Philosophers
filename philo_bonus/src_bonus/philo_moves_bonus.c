/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:40:47 by psoares           #+#    #+#             */
/*   Updated: 2021/11/28 14:24:19 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	death_check(t_philo_o *arg)
{
	while (arg->g_flag_dead == 0 && arg->data.fin_eat < arg->data.num_of_philo)
	{
		if (arg->philosofer[arg->philosofer->philo_id].need_to_eat == 0)
			exit(1);
		if (arg->data.num_of_philo == 1 || (arg->philosofer[arg->philosofer->philo_id].eating_st
			&& get_time() - arg->philosofer[arg->philosofer->philo_id].eating_st
			> arg->data.time_to_die))
		{
			if (arg->g_flag_dead == 0 && arg->philosofer[arg->philosofer->philo_id].need_to_eat != 0)
			{
				arg->g_flag_dead = 1;
				sem_wait(arg->txt_mut);
				printf("%d ms %d died\n", get_time() - arg->data.time_st,
					arg->philosofer[arg->philosofer->philo_id].philo_id + 1);
				exit(1);
			}
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
	sem_wait(arg->obj->txt_mut);
	printf("%d ms %d is sleeping\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	sem_post(arg->obj->txt_mut);
	philo_sleep_eat(arg->datas->time_to_sleep, arg);
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_detach(arg->obj->trd[arg->philo_id]);
		return ;
	}
	sem_wait(arg->obj->txt_mut);
	printf("%d ms %d is thinking\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	sem_post(arg->obj->txt_mut);
}
