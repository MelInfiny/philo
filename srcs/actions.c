/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:38 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 18:24:52 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reset_infos(t_philo *philo, int id)
{
	philo->th = 0;
	philo->id = id + 1;
	philo->start = false;
	philo->fork = false;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->meals = 0;
	philo->last_meal = 0;
	pthread_mutex_init(&philo->mutex, NULL);
}

static	int	eating(t_table *table, t_philo *philo)
{
	set_fork(philo, 1);
	set_fork(&table->philos[philo->prec], 1);
	print_fork(table, philo, 1);
	philo->eat = true;
	print_infos(table, philo);
	get_last_meal(table, philo, 1);
	if (!get_alive(philo, 2))
		return (0);
	ft_usleep(philo, table->params->eat_time);
	philo->eat = false;
	set_fork(philo, 0);
	set_fork(&table->philos[philo->prec], 0);
	return (1);
}

static	int	sleeping(t_table *table, t_philo *philo)
{
	philo->sleep = true;
	print_infos(table, philo);
	if (!get_alive(philo, 2))
		return (0);
	ft_usleep(philo, table->params->sleep_time);
	philo->sleep = false;
	return (1);
}

static int	living(t_table *table, t_philo *philo)
{
	unsigned int	meals;
	if (set_fork(philo, -1) || set_fork(&table->philos[philo->prec], -1))
		return (1);
	if (!eating(table, philo))
		return (0);	
	meals = set_meal(philo, 1) + 1;
	if (!sleeping(table, philo))
		return (0);
	philo->think = true;
	if (table->params->max_meals > 0 && meals == table->params->max_meals)
		get_satisfied(table, philo, 1);
	return (1);
}

void	*set_actions(void *table_tmp)
{
	t_table			*table;
	t_philo			*philo;
	unsigned int	prec;

	table = table_tmp;
	philo = &table->philos[get_id(table, 0)];
	prec = philo->prec;
	if (prec + 1 == philo->id)
	{
		philo->fork = true;
		print_fork(table, philo, 0);
		usleep(table->params->die_time);
		return (NULL);
	}
	if (!philo->start)
		usleep(100);
	while (get_alive(philo, 2))
		if (!living(table, philo))
			break;
	return (NULL);
}
