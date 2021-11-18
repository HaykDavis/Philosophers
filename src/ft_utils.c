/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares <psoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:45:20 by psoares           #+#    #+#             */
/*   Updated: 2021/11/18 12:26:14 by psoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	part_of_atoi(char *str, long int i, long int point)
{
	int	n;

	n = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		n = 10 * n + point * (str[i] - '0');
		i++;
	}
	return (n);
}

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
	if (str[i] >= '0' && str[i] <= '9')
		n = part_of_atoi(str, i, point);
	else
		return (0);
	return (n);
}

int	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}