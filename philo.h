/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:29 by psoares           #+#    #+#             */
/*   Updated: 2021/11/22 17:25:40 by psoares          ###   ########.fr       */
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

int flag_dead;

typedef struct philosopher_tag
{
	int philo_id;
	int eating_st;
	int sleeping_st;
    int left_fork;
    int right_fork;
	int	need_to_eat;
}				philosopher_t;

typedef struct philosopger_init
{
	int	time_st;
	int fin_eat;
	int	time_to_die;
	int	time_to_eat;
	int	must_to_eat;
	int	time_to_sleep;
	int	number_of_philosophers;
	pthread_mutex_t forkk[200];
	pthread_mutex_t *txt_mut;
}				philosopher_i;

typedef struct philo_obj
{
	philosopher_t	philosofer;
    philosopher_i	*data;
}				philo_o;

int		get_time(void);
int		ft_atoi(char *str);
void	ft_usleep(long int time);
void	all_inits(philo_o	*arguments, char **argv, int argc);
int		part_of_atoi(char *str, long int i, long int point);

#endif