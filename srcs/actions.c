/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:38 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/03 17:16:15 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reset_infos(t_table *table, t_philo *philo, int id)
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
	philo->params = table->params;
	philo->pprint = &table->print;
	philo->iinfo = &table->info;
	pthread_mutex_init(&philo->mutex, NULL);
}

static	int	eating(t_philo *philo)
{
	print_fork(philo, 1);
	print_infos(philo, 1);
	set_fork(philo, 1);
	set_fork(philo->prec, 1);
	get_last_meal(philo, 1);
	philo->eat = true;
	ft_usleep(philo, philo->params->eat_time);
	philo->eat = false;
	set_fork(philo, 0);
	set_fork(philo->prec, 0);
	set_meal(philo, 1);
	return (1);
}

static	int	sleeping(t_philo *philo)
{
	print_infos(philo, 2);
	philo->sleep = true;
	ft_usleep(philo, philo->params->sleep_time);
	philo->sleep = false;
	print_infos(philo, 0);
	philo->think = true;
	return (1);
}

static int	living(t_philo *philo)
{
	if (set_fork(philo, -1) || set_fork(philo->prec, -1))
		return (1);
	philo->think = false;
	philo->start = false;
	eating(philo);
	sleeping(philo);
	return (1);
}

void	*set_actions(void *philo_tmp)
{
	t_philo	*philo;

	philo = philo_tmp;
	if (philo->prec->id == philo->id)
	{
		print_fork(philo, 0);
		ft_usleep(philo, philo->params->die_time);
		return (NULL);
	}
	while (get_alive(philo, 2))
	{
		if (!philo->start)
		{
			usleep(100);
			philo->start = true;
		}
		living(philo);
		usleep(100);
	}
	return (NULL);
}
