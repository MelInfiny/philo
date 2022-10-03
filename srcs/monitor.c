#include "philo.h"

static size_t	get_start(t_table *table)
{
	size_t	min;

	min = table->params->eat_time * table->params->nb_philo;
	if (table->params->die_time < min)
		min = table->params->die_time;
	return (min);
}

static void	*check_end(t_table *table, int status)
{
	get_end(table, NULL, status);
	//table->end = status;
	kill_philos(table);
	return (NULL);
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;
	int	tmp;

	table = table_tmp;
	count = -1;
	usleep(get_start(table) *1000);
	while (1)
	{
		if (count < table->params->nb_philo - 1)
			count ++;
		else
			count = 0;
		tmp = get_satisfied(table, NULL, 0);
		if (tmp > 0 && tmp >= table->params->nb_philo - 1)
			return (check_end(table, -1));
		if (get_last_meal(table, &table->philos[count], 0) + table->params->die_time < get_time(table->params->start_time))
		{
			kill_philo(&table->philos[count]);
			return (check_end(table, table->philos[count].id));
		}
		usleep(200);
	}
	return (NULL);
}

