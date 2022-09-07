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
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;
	int	satisfied;

	table = table_tmp;
	count = 0;
	satisfied = 0;
	while (table->end == 0 || count < table->params->nb_philo)
	{
		if (table->philos[count].last_meal + table->params->die_time >= get_time() && table->philos[count].eat == false)
		{
			table->philos[count].alive = false;
			table->end = count;
		}
		if (table->philos[count].meals >= table->params->max_meals)
			satisfied ++;
		count ++;
	}
	if (satisfied >= table->params->nb_philo)
		table->end = -1;
	check_table(table);
	return (NULL);
}
