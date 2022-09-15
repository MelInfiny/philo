#include "philo.h"

static void	check_end(t_table *table)
{
	if (table->end == 0)
		return ;
	if (table->end == -1)
	{
		printf("END : Each philosoph is satisfied\n");
	}
	if (table->end > 0)
	{
		printf("%ld ms : %d is died\n", get_time(table->params->start_time), table->end);
	}
	return ;
}

static size_t	get_start(t_table *table)
{
	size_t	min;

	min = table->params->eat_time * table->params->nb_philo;
	if (table->params->die_time < min)
		min = table->params->die_time;
	return (min);
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;

	table = table_tmp;
	while (table->created < table->params->nb_philo || get_time(table->params->start_time) < get_start(table))
		count = -1;
	while (table->end == 0)
	{
		if (count < table->params->nb_philo - 1)
			count ++;
		else
			count = 0;
		if (table->satisfied > 0 && table->satisfied >= table->params->nb_philo - 1)
			table->end = -1;
		if (table->philos[count].last_meal + table->params->die_time <= get_time(table->params->start_time) && table->philos[count].eat == false)
		{
			table->philos[count].alive = false;
			table->end = table->philos[count].id;
		}
		usleep(200);
	}
	check_end(table);
	return (NULL);
}

