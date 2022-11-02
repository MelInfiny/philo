/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:46 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/01 16:24:07 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_alive(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->iinfo);
	res = philo->alive;
	if (status == 1)
		philo->alive = true;
	else if (status == 0)
		philo->alive = false;
	pthread_mutex_unlock(philo->iinfo);
	return (res);
}

int	get_last_meal(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->iinfo);
	res = philo->last_meal;
	if (status == 1)
		philo->last_meal = get_time(philo->params->start_time);
	pthread_mutex_unlock(philo->iinfo);
	return (res);
}

int	get_created(t_table *table, int status)
{
	int	res;

	pthread_mutex_lock(&table->print);
	res = table->created;
	if (status)
		res = ++table->created;
	pthread_mutex_unlock(&table->print);
	return (res);
}
