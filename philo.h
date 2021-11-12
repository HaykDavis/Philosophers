/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:29 by psoares           #+#    #+#             */
/*   Updated: 2021/11/12 17:58:14 by psoares          ###   ########.fr       */
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

pthread_mutex_t forkk[200];

typedef struct philosopher_tag
{
	int philo_number;
    unsigned left_fork;
    unsigned right_fork;

}				philosopher_t;

typedef struct philosopger_init
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;

	philosopher_t forkys;
}				philosopher_i;

typedef struct philo_obj
{
	philosopher_t *philosofer;
    philosopher_i *data;
}				philo_o;

int	ft_atoi(char *str);
int	part_of_atoi(char *str, long int i, long int point);

#endif