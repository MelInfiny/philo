#include "philo.h"

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->params);
	free(table);
	exit(1);
}
