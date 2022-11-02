/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:22:07 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/02 14:28:33 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_start_time(void)
{
	struct timeval	time;
	unsigned long	mstime;
	unsigned long	stime;

	gettimeofday(&time, NULL);
	stime = time.tv_sec * 1000;
	mstime = time.tv_usec / 1000;
	return (stime + mstime);
}

unsigned long	get_time(unsigned long start)
{
	struct timeval	time;
	unsigned long	mstime;
	unsigned long	stime;

	gettimeofday(&time, NULL);
	stime = time.tv_sec * 1000;
	mstime = time.tv_usec / 1000;
	return ((stime + mstime) - start);
}

void	print_infos(t_philo *philo)
{
	unsigned long	time;

	time = philo->params->start_time;
	pthread_mutex_lock(philo->pprint);
	if (philo->alive)
	{
		if (philo->sleep)
			printf("%ld %d is sleeping\n", get_time(time), philo->id);
		else if (philo->eat)
			printf("%ld %d is eating\n", get_time(time), philo->id);
		else if (philo->think)
			printf("%ld %d is thinking\n", get_time(time), philo->id);
	}
	pthread_mutex_unlock(philo->pprint);
}

void	print_fork(t_philo *philo, int status)
{
	unsigned long	time;

	time = philo->params->start_time;
	pthread_mutex_lock(philo->pprint);
	if (philo->alive)
	{
		printf("%ld %d has taken a fork\n", get_time(time), philo->id);
		if (status)
			printf("%ld %d has taken a fork\n", get_time(time), philo->id);
	}
	pthread_mutex_unlock(philo->pprint);
}
