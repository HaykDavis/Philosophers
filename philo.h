/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:29 by psoares           #+#    #+#             */
/*   Updated: 2021/11/17 19:04:34 by psoares          ###   ########.fr       */
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
	int	time_st;
	int philo_id;
	int eating_st;
	int	must_to_eat;
	int	finish_eating;
    int left_fork;
    int right_fork;

}				philosopher_t;

typedef struct philosopger_init
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_philosophers;
}				philosopher_i;

typedef struct philo_obj
{
	pthread_mutex_t forkk[200];
	philosopher_t	philosofer;
    philosopher_i	*data;
}				philo_o;

int	get_time(void);
int	ft_atoi(char *str);
void all_inits(philo_o	*arguments, char **argv);
int	part_of_atoi(char *str, long int i, long int point);

#endif