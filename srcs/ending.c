/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:43 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/01 16:28:55 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_mutex(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[count].mutex);
		count ++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->info);
}

void	free_table(t_table *table)
{
	free_mutex(table);
	free(table->philos);
	free(table->params);
	free(table);
}

void	error_philo(t_table *table, char *msg)
{
	perror(msg);
	kill_philos(table);
	return ;
}

void	kill_philos(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		get_alive(&table->philos[count], 0);
		count ++;
	}
}

void	kill_philo(t_philo *philo)
{
	get_alive(philo, 0);
}
