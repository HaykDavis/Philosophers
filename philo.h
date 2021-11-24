/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:29 by psoares           #+#    #+#             */
/*   Updated: 2021/11/23 16:05:17 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct t_philosopherag
{
	int	philo_id;
	int	eating_st;
	int	sleeping_st;
	int	left_fork;
	int	right_fork;
	int	need_to_eat;
	struct philosopger_init *datas;
	struct t_philo_obj *obj;
}				t_philosopher;

typedef struct philosopger_init
{
	int				time_st;
	int				fin_eat;
	int				time_to_die;
	int				time_to_eat;
	int				must_to_eat;
	int				time_to_sleep;
	int				num_of_philo;
}				t_philo;

typedef struct t_philo_obj
{
	int				g_flag_dead;
	pthread_mutex_t	*forkk;
	pthread_mutex_t	*txt_mut;
	t_philosopher	*philosofer;
	t_philo			data;
}				t_philo_o;

int		get_time(void);
int		ft_atoi(char *str);
void	ft_usleep(long int time);
void	eat_next(t_philosopher	*arg);
void	sleeps(t_philosopher	*arg);
void	philo_sleep_eat(int time, t_philosopher	*arg);
void	death_check(t_philo_o *arg);
void	if_dead(t_philo_o *arg, int i);
void	all_inits(t_philo_o	*arguments, char **argv, int argc);
int		part_of_atoi(char *str, long int i, long int point);

#endif