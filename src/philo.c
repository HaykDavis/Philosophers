/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/18 20:01:51 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_sleep_eat(int time)
{
	struct timeval	tv;
	int				cur_time;
	int				res;

	gettimeofday(&tv, NULL);
	cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	res = cur_time + time;
	while (cur_time < res && flag_dead == 0)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		cur_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (flag_dead == 1)
			break ;
	}
}

void sleeps(philo_o	*arg)
{
	if (flag_dead == 1)
		return ;
	printf("%d ms %d is sleeping\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
	pthread_mutex_unlock(&arg->forkk[arg->philosofer.left_fork]);
	pthread_mutex_unlock(&arg->forkk[arg->philosofer.right_fork]);
	philo_sleep_eat(arg->data->time_to_sleep);
	if (flag_dead == 1)
		return ;
	printf("%d ms %d is thinking\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
		
}

void eat(philo_o	*arg)
{
	if (flag_dead == 1)
		return ;
	pthread_mutex_lock(&arg->forkk[arg->philosofer.left_fork]);
	printf("%d ms %d has taken fork\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
		
	if (flag_dead == 1)
		return ;
	pthread_mutex_lock(&arg->forkk[arg->philosofer.right_fork]);
	printf("%d ms %d has taken fork\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
		
	printf("%d ms %d is eating\n", get_time() - arg->data->time_st,
		arg->philosofer.philo_id + 1);
		
	arg->philosofer.eating_st = get_time();
	
	// printf("eating22 = %d\n", arg->philosofer.eating_st);
	
	philo_sleep_eat(arg->data->time_to_eat);
	// pthread_mutex_unlock(&arg->forkk[arg->philosofer.left_fork]);
	// pthread_mutex_unlock(&arg->forkk[arg->philosofer.right_fork]);
	// if (philo->need_to_eat > 0)
	// 	philo->need_to_eat--;
	// if (philo->need_to_eat == 0)
	// 	philo->input->finish_eating++;
}

void *start_philo(void *tmp)
{
	philo_o	*arg;

	arg = (philo_o *)tmp;
	if (arg->philosofer.philo_id % 2 == 0)
		usleep(100);
	while (flag_dead != 1) //&&
	{
		eat(arg);
		sleeps(arg);
	}
	return NULL;
}


void	death_check(philo_o *arguments)
{
	static int	i;

	while (flag_dead == 0)
	{
		// if (i == data->data->number_of_philosophers - 1)
		// 	i = 0;
		// printf("eating = %d\n", arguments[i].philosofer.eating_st);
		// printf("time_to_die = %d\n", arguments->data->time_to_die);
		usleep(1000);
		if (get_time() - arguments[i].philosofer.eating_st > arguments->data->time_to_die)
		{
			// pthread_mutex_lock(data->philo[i].print_lock);
			if (flag_dead == 0)
				printf("%d ms %d died\n", get_time() - arguments->data->time_st,
					arguments[i].philosofer.philo_id + 1);
			// pthread_mutex_unlock(data->philo[i].print_lock);
			flag_dead = 1;
			break ; 
		}
		i = (i + 1) % arguments->data->number_of_philosophers;
	}
}

int main(int argc, char **argv)
{
	int					i;
	(void)				argc;
	pthread_t			trd[ft_atoi(argv[1])];
	philo_o				arguments[ft_atoi(argv[1])];
	
	arguments->data = malloc(sizeof(philosopher_i));
	all_inits(arguments, argv);
	i = 0;
	arguments->data->time_st = get_time();
	// printf("%d\n", arguments->data->time_st);
	while (i < ft_atoi(argv[1]))
		pthread_create(&trd[i], NULL, start_philo, &arguments[i]), i++;
	// death_check(arguments);
	death_check(arguments);
	free(arguments->data);
	return (0);
}