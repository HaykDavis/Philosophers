/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/22 18:33:44 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleep_eat(int time)
{
	int	cur_time;
	int	res;

	cur_time = get_time();
	res = cur_time + time;
	while (cur_time < res && flag_dead == 0)
	{
		usleep(100);
		cur_time = get_time();
		if (flag_dead == 1)
			break ;
	}
}

void sleeps(philo_o	*arg)
{
	if (flag_dead == 1)
		return ;
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d is sleeping\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	philo_sleep_eat(arg->data->time_to_sleep);
	if (flag_dead == 1)
		return ;
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d is thinking\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
}

void eat(philo_o	*arg)
{
	pthread_mutex_lock(&arg->data->forkk[arg->philosofer.left_fork]);
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	if (flag_dead == 1)
	{
		pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.left_fork]);
		return ;
	}
	pthread_mutex_lock(&arg->data->forkk[arg->philosofer.right_fork]);
	pthread_mutex_lock(arg->data->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(arg->data->txt_mut);
	if (flag_dead == 1)
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

void *start_philo(void *tmp)
{
	philo_o	*arg;

	arg = (philo_o *)tmp;
	if (arg->philosofer.philo_id % 2 == 0)
		usleep(100);
	while (flag_dead != 1 && arg->philosofer.need_to_eat != 0)
		eat(arg);
	return NULL;
}

void if_dead(philo_o *arguments, int i)
{
	if (arguments[i].philosofer.eating_st && get_time() - arguments[i].philosofer.eating_st > arguments->data->time_to_die)
	{
		if (flag_dead == 0 && arguments[i].philosofer.need_to_eat != 0)
		{
			flag_dead = 1;
			pthread_mutex_lock(arguments->data->txt_mut);
			printf("%d ms %d died\n", get_time() - arguments->data->time_st,
				arguments[i].philosofer.philo_id + 1);
			pthread_mutex_unlock(arguments->data->txt_mut);
		}
	}
}

void	death_check(philo_o *arguments)
{
	int	i;
	
	i = 0;
	while (flag_dead == 0 && arguments->data->fin_eat < arguments->data->number_of_philosophers)
	{
		if (i == arguments->data->number_of_philosophers - 1)
			i = 0;
		if_dead(arguments, i);
		i++;
	}
}


int main(int argc, char **argv)
{
	int					i;
	(void)				argc;
	pthread_t			trd[ft_atoi(argv[1])];
	philo_o				arguments[ft_atoi(argv[1])];
	
	arguments->data = malloc(sizeof(philosopher_i));
	arguments->data->time_st = get_time();
	all_inits(arguments, argv, argc);
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_create(&trd[i], NULL, start_philo, &arguments[i]), i++;
	death_check(arguments);
	free(arguments->data);
	return (0);
}