#include "philo.h"

void	*set_actions(void *table_tmp)
{
	t_table	*table;
	t_philo *philo;

	table = table_tmp;
	philo = &table->philos[table->id];
	while (table->end == 0)
	{
		if (philo->fork == 1)
			get_meal(table, philo);
		else if (is_available(table, philo))
			get_meal(table, philo);
		if (philo->meals == table->params->max_meals)
			table->satisfied ++;
	}
	return (NULL);
}

void	get_meal(t_table *table, t_philo *philo)
{
	philo->fork = true;
	set_infos(table, philo, 1, true);		// eat
	usleep(table->params->eat_time * 1000);		
	set_infos(table, philo, 0, false);		// fork
	set_infos(table, philo, 1, false);
	philo->last_meal = get_time(table->params->start_time);
	set_infos(table, philo, 4, false);		// last meal
	set_infos(table, philo, 2, true);		// sleep
	usleep(table->params->sleep_time * 1000);
	set_infos(table, philo, 2, false);
	set_infos(table, philo, 3, true);		//think
}

int	is_available(t_table *table, t_philo *philo)
{
	int	id;
	int	next;
	int	prec;

	id = philo->id - 1;
	if (id == 0)
		prec = table->params->nb_philo - 1;
	else
		prec = id - 1;
	if (id == table->params->nb_philo - 1)
		next = 0;
	else
		next = id + 1;
	if (table->philos[prec].fork == 1 || table->philos[next].fork == 1)
		return (0);
	return (1);
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