/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/29 14:30:39 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat_next(t_philosopher	*arg)
{
	arg->eating_st = get_time();
	pthread_mutex_lock(arg->obj->txt_mut);
	printf("%d ms %d is eating\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	pthread_mutex_unlock(arg->obj->txt_mut);
	philo_sleep_eat(arg->datas->time_to_eat, arg);
	pthread_mutex_unlock(&arg->obj->forkk[arg->left_fork]);
	pthread_mutex_unlock(&arg->obj->forkk[arg->right_fork]);
	sleeps(arg);
	if (arg->need_to_eat > 0)
		arg->need_to_eat--;
	if (arg->need_to_eat == 0)
		arg->datas->fin_eat++;
}

void	eat(t_philosopher	*arg)
{
	pthread_mutex_lock(&arg->obj->forkk[arg->left_fork]);
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_mutex_unlock(&arg->obj->forkk[arg->left_fork]);
		pthread_detach(arg->obj->trd[arg->philo_id]);
		return ;
	}
	pthread_mutex_lock(arg->obj->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	pthread_mutex_unlock(arg->obj->txt_mut);
	pthread_mutex_lock(&arg->obj->forkk[arg->right_fork]);
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_mutex_unlock(&arg->obj->forkk[arg->right_fork]);
		pthread_detach(arg->obj->trd[arg->philo_id]);
		return ;
	}
	pthread_mutex_lock(arg->obj->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	pthread_mutex_unlock(arg->obj->txt_mut);
	eat_next(arg);
}

void	*start_philo(void *tmp)
{
	t_philosopher	*philosofer;

	philosofer = (t_philosopher *)tmp;
	if (philosofer->philo_id % 2 == 0)
		usleep(100);
	while (philosofer->obj->g_flag_dead != 1 && philosofer->need_to_eat != 0)
		eat(philosofer);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	t_philo_o	*arg;

	if (check_arg(argc, argv) == 0)
		return (0);
	arg = (t_philo_o *)malloc(sizeof(t_philo_o));
	if (!arg)
		return (0);
	all_inits(arg, argv, argc);
	arg->data.time_st = get_time();
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&arg->trd[i], NULL, start_philo, &arg->philosofer[i]);
		i++;
	}
	death_check(arg);
	frees(arg);
	return (0);
}
