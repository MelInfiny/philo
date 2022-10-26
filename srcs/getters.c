/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:46 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 13:10:20 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_eat(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->eat;
	if (status == 1)
		philo->eat = true;
	else if (status == 0)
		philo->eat = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_alive(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->alive;
	if (status == 1)
		philo->alive = true;
	else if (status == 0)
		philo->alive = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_satisfied(t_table *table, t_philo *philo, int status)
{
	int	res;

	if (philo == NULL)
		pthread_mutex_lock(&table->print);
	else
		pthread_mutex_lock(philo->pprint);
	res = table->satisfied;
	if (status == 1)
		table->satisfied ++;
	pthread_mutex_unlock(&table->print);
	return (res);
}

int	get_last_meal(t_table *table, t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->last_meal;
	if (status == 1)
		philo->last_meal = get_time(table->params->start_time);
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_id(t_table *table, int status)
{
	int	res;

	pthread_mutex_lock(&table->print);
	res = table->id;
	if (status > 0)
		table->id = status;
	pthread_mutex_unlock(&table->print);
	return (res);
}
