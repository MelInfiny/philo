#include "philo.h"

void	*set_actions(void *table_tmp)
{
	t_table	*table;
	t_philo *philo;
	int	prec;
	
	table = table_tmp;
	philo = &table->philos[table->id];
	while (table->created < table->params->nb_philo)
		prec ++;
	prec = get_prec(table, philo);
	while (table->end == 0)
	{
		if (!philo->start)
			usleep(1000);
		if (!pthread_mutex_lock(&philo->mutex))
		{
			set_infos(table, philo, 0, true);		// fork
			if (!pthread_mutex_lock(&table->philos[prec].mutex))
				get_meal(table, philo, prec);
			else
			pthread_mutex_unlock(&philo->mutex);
		}
	}
	return (NULL);
}

void	get_meal(t_table *table, t_philo *philo, int prec)
{
	set_infos(table, philo, 0, true);		// fork
	set_infos(table, philo, 0, false);
	set_infos(table, philo, 1, true);		// eat
	usleep(table->params->eat_time * 1000);	
	philo->last_meal = get_time(table->params->start_time); //	die when he eats
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&table->philos[prec].mutex);

	set_infos(table, philo, 1, false);
	set_infos(table, philo, 2, true);		// sleep
	set_infos(table, philo, 4, false);		// last meal
	usleep(table->params->sleep_time * 1000);
	set_infos(table, philo, 2, false);
	set_infos(table, philo, 3, true);		//think
	if (table->params->max_meals > 0 && philo->meals == table->params->max_meals)
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
