/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:26 by psoares           #+#    #+#             */
/*   Updated: 2021/11/29 16:59:51 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	eat_next(t_philosopher	*arg)
{
	arg->eating_st = get_time();
	sem_wait(arg->obj->txt_mut);
	printf("%d ms %d is eating\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	sem_post(arg->obj->txt_mut);
	philo_sleep_eat(arg->datas->time_to_eat, arg);
	sem_post(arg->obj->forkk);
	sem_post(arg->obj->forkk);
	sleeps(arg);
	if (arg->need_to_eat > 0)
		arg->need_to_eat--;
	if (arg->need_to_eat == 0)
		arg->datas->fin_eat++;
}

void	eat(t_philosopher	*arg)
{
	sem_wait(arg->obj->forkk);
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_detach(arg->obj->trd[arg->philo_id]);
		sem_post(arg->obj->forkk);
		return ;
	}
	sem_wait(arg->obj->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	sem_post(arg->obj->txt_mut);
	sem_wait(arg->obj->forkk);
	if (arg->obj->g_flag_dead == 1)
	{
		pthread_detach(arg->obj->trd[arg->philo_id]);
		sem_post(arg->obj->forkk);
		return ;
	}
	sem_wait(arg->obj->txt_mut);
	printf("%d ms %d has taken fork\n", get_time() - arg->datas->time_st,
		arg->philo_id + 1);
	sem_post(arg->obj->txt_mut);
	eat_next(arg);
}

void	*start_philo(void *tmp)
{
	t_philosopher	*philosofer;

	philosofer = (t_philosopher *)tmp;
	if (philosofer->philo_id % 2 == 0)
		usleep((philosofer->datas->time_to_die / 2));
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
	if (pros_create(arg) == 0)
		exit(1);
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < arg->data.num_of_philo)
	{
		kill(arg->philosofer[i].pid, SIGKILL);
		i++;
	}
	frees(arg);
	return (0);
}
