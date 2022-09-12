#include "philo.h"

void	*set_actions(void *table_tmp)
{
	t_table	*table;
	t_philo *philo;
	int	prec;

	table = table_tmp;
	philo = &table->philos[table->id];
	prec = get_prec(table, philo);
	while (table->end == 0)
	{
		if (philo->fork == 1)
			get_meal(table, philo);
		else if (!pthread_mutex_lock(&philo->mutex) && !pthread_mutex_lock(&table->philos[prec].mutex))
			get_meal(table, philo);
	}
	return (NULL);
}

void	get_meal(t_table *table, t_philo *philo)
{
	int	prec;
	
	prec = get_prec(table, philo);
	philo->fork = true;
	set_infos(table, philo, 1, true);		// eat
	set_infos(table, philo, 0, false);		// fork
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
