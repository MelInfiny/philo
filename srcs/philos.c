/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:22:02 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/01 15:07:40 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_table *table)
{
	int	count;

	count = 0;
	table->philos = calloc(table->params->nb_philo, sizeof(t_philo));
	if (!table->philos)
	{
		perror("Allocation philos ");
		free(table->params);
		free(table);
		exit(1);
	}
	while (count < table->params->nb_philo)
	{
		reset_infos(table, &table->philos[count], count);
		if (count % 2 == 0 && count != table->params->nb_philo -1)
			table->philos[count].start = true;
		count ++;
	}
	prec_philo(table);
}

void	init_philos(t_table *table)
{
	int		count;

	count = 0;
	table->params->start_time = get_start_time();
	while (count < table->params->nb_philo)
	{
		if (pthread_create(&table->philos[count].th,
				NULL, &set_actions, (void *) &table->philos[count]) != 0)
		{
			return (error_philo(table, "cretation thread "));
		}
		//usleep(500);
		count ++;
	}
}

void	join_philos(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		if (pthread_join(table->philos[count].th, NULL))
		{
			error_philo(table, "join thread ");
			return ;
		}
		count ++;
	}
}

void	prec_philo(t_table *table)
{
	int	id;
	int	prec;

	id = 0;
	while (id < table->params->nb_philo)
	{
		if (id == 0)
			prec = table->params->nb_philo - 1;
		else
			prec = id - 1;
		table->philos[id].prec = &table->philos[prec];
		id ++;
	}
}
