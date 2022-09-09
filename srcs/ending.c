#include "philo.h"

void	check_table(t_table *table)
{
	if (table->end == 0)
		return ;
	if (table->end == -1)
	{
		printf("END : Each philosoph is satisfied\n");
	}
	if (table->end > 0)
	{
		print_time(table->params->start_time);
		printf("%d is died\n", table->philos[table->end].id);
	}
	printf("table end for %d\n\n", table->end);
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;
	int	satisfied;

	table = table_tmp;
	count = 0;
	satisfied = 0;
	while (table->end == 0)
	{
	//	printf("%ld philo id %d\n", get_time(table->params->start_time), table->philos[count].id);	//db
		if (satisfied >= table->params->nb_philo - 1)
			table->end = -1;
		if (table->philos[count].last_meal + table->params->die_time <= get_time(table->params->start_time) && table->philos[count].eat == false)
		{
			table->philos[count].alive = false;
			table->end = count;
		}
		if (count < table->params->nb_philo)
			count ++;
		else
			count = 0;
	}
	check_table(table);
	return (NULL);
}
