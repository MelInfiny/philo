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
	int	res;

	table->end = status;
	res = pthread_mutex_lock(&table->print);
	if (table->end == -1)
	{
		printf("END : Each philosoph is satisfied\n");
	}
	if (table->end > 0)
	{
		printf("%ld ms : %d is died\n", get_time(table->params->start_time), table->end);
	}
	if (!res)
		pthread_mutex_unlock(&table->print);
	kill_philos(table);
	return (NULL);
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;

	table = table_tmp;
	count = -1;
	usleep(get_start(table) *1000);
	while (1)
	{
		if (count < table->params->nb_philo - 1)
			count ++;
		else
			count = 0;
		if (table->satisfied > 0 && table->satisfied >= table->params->nb_philo - 1)
			return (check_end(table, -1));
		if (table->philos[count].last_meal + table->params->die_time < get_time(table->params->start_time) && table->philos[count].eat == false)
		{
			kill_philo(&table->philos[count]);
			return (check_end(table, table->philos[count].id));
		}
		usleep(200);
	}
	return (NULL);
}

