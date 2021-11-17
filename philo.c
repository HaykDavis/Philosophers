/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/17 16:22:34 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(int time_to, philo_o *arg)
{
	struct timeval	tv;
	int				cur_time;
	int				res;

	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	res = cur_time + time_to; // если все ок, то он жив
	while (cur_time < res && flag_dead == 0)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (flag_dead == 1)
			break ;
	}
}

void eat(philo_o	*arg)
{
	pthread_mutex_lock(&arg->data->forkk[arg->philosofer.left_fork]);
	printf("%d ms %d has taken fork\n", get_time() - arg->philosofer.time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_lock(&arg->data->forkk[arg->philosofer.right_fork]);
	printf("%d ms %d has taken fork\n", get_time() - arg->philosofer.time_st,
		arg->philosofer.philo_id + 1);
	// printf("Philo № %d is eating %d %d\n", arg->philosofer.philo_id, arg->philosofer.left_fork, arg->philosofer.right_fork);
	// sleep(1); // arg->philosofer->eating_st = get_time();
	// philo_sleep(arg->moves->time_to_eat, arg);
	
	pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.left_fork]);
	pthread_mutex_unlock(&arg->data->forkk[arg->philosofer.right_fork]);
	// if (philo->need_to_eat > 0)
	// 	philo->need_to_eat--;
	// if (philo->need_to_eat == 0)
	// 	philo->input->finish_eating++;
	// printf("Philo № %d finished dinner\n", arg->philosofer->philo_number);
}

void *start_philo(void *tmp)
{
	philo_o	*arg;

	arg = (philo_o *)tmp;
	// printf("time3: %d\n", arg->moves->time_st);
	if (arg->philosofer.philo_id % 2 == 0)
		usleep(100);
	while (flag_dead == 0) //&&
	{
		eat(arg);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	int					i;
	int					z;
	pthread_t			trd[ft_atoi(argv[1])];
	philo_o				arguments[ft_atoi(argv[1])];
	
	arguments->data = malloc(sizeof(philosopher_i));
	all_inits(arguments, argv);
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_create(&trd[i], NULL, start_philo, &arguments[i]), i++;
	while(1)
	{}
	free(arguments->data);
	return (0);
}