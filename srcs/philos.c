#include "philo.h"

int	init_philo(t_table *table)
{
	int	id;

	id = table->id;
	reset_infos(table);
	if (id % 2 == 0)
		table->philos[id].fork = 1;
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
	if (is_available(table))
	{
		set_infos(table, 0, true);		// fork
		set_infos(table, 1, true);			// eat
		usleep(table->params->eat_time * 1000);		
		set_infos(table, 1, false);
		set_infos(table, 0, false);		// fork
		table->philos[id].last_meal = get_time() + table->params->eat_time;
		set_infos(table, 4, true);		// last meal
		set_infos(table, 2, true);		// sleep
		usleep(table->params->sleep_time * 1000);
		set_infos(table, 2, false);
	}
	set_infos(table, 3, true);		//think
	return (NULL);
}

int	is_available(t_table *table)
{
	int	id;
	int	next;
	int	prec;

	id = table->id;
	if (id == 0)
		prec = table->params->nb_philo - 1;
	else
		prec = id - 1;
	if (id == table->params->nb_philo)
		next = 0;
	else
		next = id + 1;
	if (table->philos[prec].fork == 1 || table->philos[next].fork == 1)
		return (0);
	return (1);
}

void	set_infos(t_table *table, int status, bool state)
{
	int	id;

	id = table->id;
	if (status == 0)
		table->philos[id].fork = state;
	else if (status == 1)
		table->philos[id].eat = state;
	else if (status == 2)
		table->philos[id].sleep = state;
	else if (status == 3)
		table->philos[id].think = state;
	else if (status == 4)
		table->philos[id].meals ++;
	if (status != 3)
		table->philos[id].think = false;
	if (state)
		print_infos(&table->philos[id], table->params->start_time);
}

void	reset_infos(t_table *table)
{
	int	id;

	id = table->id;
	table->philos[id].id = id + 1;
	table->philos[id].eat = false;
	table->philos[id].sleep = false;
	table->philos[id].think = false;
	table->philos[id].fork = false;
	table->philos[id].alive = true;
	table->philos[id].meals = 0;
	table->philos[id].last_meal = table->params->start_time;
}
