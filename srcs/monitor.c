/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:54 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 15:41:54 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static size_t	get_start(t_table *table)
{
	size_t	min;

	min = table->params->eat_time * table->params->nb_philo;
	if (table->params->die_time < min)
		min = table->params->die_time;
	return (min);
}
*/
static void	*check_end(t_table *table, int status)
{
	if (status == -1)
		printf("Each philosophers is satisfied\n");
	if (status > 0)
		kill_philo(&table->philos[status -1]);
	set_end(table, NULL, status);
	kill_philos(table);
	return (NULL);
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int		count;
	int		tmp;

	table = table_tmp;
	count = -1;
	//usleep(get_start(table) * 1000);
	while (1)
	{
		if (count < table->params->nb_philo - 1)
			count ++;
		else
			count = 0;
		tmp = get_satisfied(table, NULL, 0);
		if (tmp > 0 && tmp >= table->params->nb_philo - 1)
			return (check_end(table, -1));
		if (get_last_meal(table, &table->philos[count], 0)
			+ table->params->die_time < get_time(table->params->start_time))
			return (check_end(table, table->philos[count].id));
		usleep(200);
	}
	return (NULL);
}
