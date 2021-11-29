/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:20 by psoares           #+#    #+#             */
/*   Updated: 2021/11/29 15:56:55 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	ft_atoi(char *str)
{
	int	i;
	int	point;
	int	n;

	i = 0;
	n = 0;
	point = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			point *= -1;
		i++;
	}
	while (str[i])
	{
		n = 10 * n + point * (str[i] - '0');
		i++;
	}
	return (n);
}

int	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	frees(t_philo_o *arg)
{
	sem_unlink("/forks");
	sem_unlink("/print_lock");
	sem_close(arg->forkk);
	sem_close(arg->txt_mut);
	free(arg->philosofer);
	sem_post(arg->txt_mut);
	free(arg);
}

int	check_arg(int argc, char **argv)
{
	int	i;
	int	z;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) > 200 || ft_atoi(argv[3]) < 60)
		return (0);
	i = 1;
	while (argv[i])
	{
		z = 0;
		while (argv[i][z])
		{
			if (argv[i][z] < '0' || argv[i][z] > '9')
				return (0);
			z++;
		}
		i++;
	}
	return (1);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
