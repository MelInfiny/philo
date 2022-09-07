#include "philo.h"
/*
int	init_philo(t_param *params, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->fork = false;
	philo->last_meal = params->start_time;
	philo->meals = 0;
	if (pthread_create(&philo->th, NULL, &print_infos, (void *) philo) != 0)
	{
		perror("creation thread");
		return (0);
	}
	if (pthread_join(philo->th, NULL) != 0)
	{
		perror("join thread");
		return(0);
	}
	return (1);
}
*/
int	init_philo(t_table *table)
{
	int	id;

	id = table->id;
	table->philos[id].id = id + 1;
	table->philos[id].eat = false;
	table->philos[id].sleep = false;
	table->philos[id].think = false;
	table->philos[id].alive = true;
	table->philos[id].fork = false;
	table->philos[id].last_meal = table->params->start_time;
	table->philos[id].meals = 0;
	if (pthread_create(&table->philos[id].th, NULL, &set_actions, (void *) table) != 0)
	{
		perror("creation thread");
		return (0);
	}
	if (pthread_join(table->philos[id].th, NULL) != 0)
	{
		perror("join thread");
		return(0);
	}
	return (1);
}

void	*set_actions(void *table_tmp)
{
	t_table	*table;
	int	id;

	table = table_tmp;
	id = table->id;
	//while (table->end == 0)
	while (table->philos[id].meals < table->params->max_meals)
	{
		set_infos(&table->philos[id], 3, false);		//think
		set_infos(&table->philos[id], 0, true);		// fork
		set_infos(&table->philos[id], 1, true);		// eat
		usleep(table->params->eat_time);		
		set_infos(&table->philos[id], 1, false);
		table->philos[id].last_meal = get_time() + table->params->eat_time;
		set_infos(&table->philos[id], 4, true);		// last meal
		set_infos(&table->philos[id], 2, true);		// sleep
		usleep(table->params->sleep_time);
		set_infos(&table->philos[id], 2, false);		
		set_infos(&table->philos[id], 3, true);		//think		
	}
	return (NULL);
}

void	set_infos(t_philo *philo, int status, bool state)
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
	else
		philo->alive = false;
	print_infos(philo);
}
