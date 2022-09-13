#include "philo.h"

void	*set_actions(void *table_tmp)
{
	t_table	*table;
	t_philo *philo;
	int	prec;
	
	table = table_tmp;
	philo = &table->philos[table->id];
	reset_infos(philo, table->id);
	prec = get_prec(table, philo);
	printf("prec = %d\n", prec);
	if (philo->start)
	{
		if (!pthread_mutex_lock(&philo->mutex) && !pthread_mutex_lock(&table->philos[prec].mutex))
			get_meal(table, philo);
	}
	else 
		usleep(500);
	while (table->end == 0)
	{
		if (!pthread_mutex_lock(&philo->mutex) && !pthread_mutex_lock(&table->philos[prec].mutex))
			get_meal(table, philo);
	}
	return (NULL);
}

void	get_meal(t_table *table, t_philo *philo)
{
	int	prec;
	
	prec = get_prec(table, philo);
	set_infos(table, philo, 0, true);		// eat
	set_infos(table, philo, 0, true);		// fork
	set_infos(table, philo, 0, false);		// fork
	set_infos(table, philo, 1, true);		// eat
	usleep(table->params->eat_time * 1000);	
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&table->philos[prec].mutex);

	set_infos(table, philo, 1, false);
	set_infos(table, philo, 2, true);		// sleep
	philo->last_meal = get_time(table->params->start_time);
	set_infos(table, philo, 4, false);		// last meal
	usleep(table->params->sleep_time * 1000);
	set_infos(table, philo, 2, false);
	set_infos(table, philo, 3, true);		//think
	if (philo->meals == table->params->max_meals)
		table->satisfied ++;
}

void	set_infos(t_table *table, t_philo *philo, int status, bool state)
{
	if (status == 0)
		philo->fork = state;
	else if (status == 1)
		philo->eat = state;
	else if (status == 2)
		philo->sleep = state;
	else if (status == 3)
		philo->think = state;
	else if (status == 4)
		philo->meals ++;
	if (status != 3)
		philo->think = false;
	if (state && table->end == 0)
		print_infos(philo, table->params->start_time);
}
