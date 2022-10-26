/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:07:26 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 13:10:36 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_end(t_table *table, t_philo *philo, int status)
{
	int	res;

	if (philo == NULL)
		pthread_mutex_lock(&table->print);
	else
		pthread_mutex_lock(philo->pprint);
	res = table->end;
	table->end = status;
	if (status == -1)
		printf("END : Each philosoph ils satisfied\n");
	else if (status > 0)
		printf("%ld ms : %d is died\n",
			get_time(table->params->start_time), table->end);
	pthread_mutex_unlock(&table->print);
	return (res);
}

int	set_meal(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->meals;
	if (status)
		philo->meals ++;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	set_fork(t_philo *philo, int status)
{	
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->fork;
	if (status == 1)
		philo->fork = true;
	else if (status == 0)
		philo->fork = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}