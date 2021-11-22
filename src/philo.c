/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/22 19:41:28 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo_o	*arg)
{
	pthread_mutex_lock(&arg->data->forkk[arg->philosofer.left_fork]);
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	if (g_flag_dead == 1)
	{
		pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.left_fork]);
		return ;
	}
	pthread_mutex_lock(&arg->data->forkk[arg->philosofer.right_fork]);
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	if (g_flag_dead == 1)
	{
		pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.right_fork]);
		return ;
	}
	arg->philosofer.eating_st = get_time();
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d is eating\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	philo_sleep_eat(arg->data->time_to_eat);
	pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.left_fork]);
	pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.right_fork]);
	sleeps(arg);
	if (arg->philosofer.need_to_eat > 0)
		arg->philosofer.need_to_eat--;
	if (arg->philosofer.need_to_eat == 0)
		arg->data->fin_eat++;
}

void	*start_philo(void *tmp)
{
	t_philo_o	*arg;

	arg = (t_philo_o *)tmp;
	if (arg->philosofer.philo_id % 2 == 0)
		usleep(100);
	while (g_flag_dead != 1 && arg->philosofer.need_to_eat != 0)
		eat(arg);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int			i;
	pthread_t	trd[ft_atoi(argv[1])];
	t_philo_o	arg[ft_atoi(argv[1])];

	arg->data = malloc(sizeof(t_philo));
	arg->data->time_st = get_time();
	all_inits(arg, argv, argc);
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_create(&trd[i], NULL, start_philo, &arg[i]), i++;
	death_check(arg);
	free(arg->data);
	return (0);
}
