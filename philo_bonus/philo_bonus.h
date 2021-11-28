/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:29 by psoares           #+#    #+#             */
/*   Updated: 2021/11/27 22:11:38 by psoares          ###   ########.fr       */
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
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct t_philosopherag
{
	int						philo_id;
	int						eating_st;
	int						sleeping_st;
	int						left_fork;
	int						right_fork;
	int						need_to_eat;
	pid_t					pid;
	struct t_philo_obj		*obj;
	struct philosopger_init	*datas;
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
	t_philo			data;
	t_philosopher	*philosofer;
	sem_t			*forkk;
	sem_t			*txt_mut;
	pthread_t		trd[200];
}				t_philo_o;

int		get_time(void);
int		ft_atoi(char *str);
void	frees(t_philo_o *arg);
void	ft_usleep(long int time);
void	sleeps(t_philosopher *arg);
void	death_check(t_philo_o *arg);
void	eat_next(t_philosopher	*arg);
void	ft_usleep(long int time_in_ms);
int		check_arg(int argc, char **argv);
void	philo_sleep_eat(int time, t_philosopher	*arg);
void	all_inits(t_philo_o	*arguments, char **argv, int argc);

#endif