#include "philo.h"

int	init_philo(t_table *table)
{
	int	id;

	id = table->id;
	print_time(table->params->start_time);
	printf("init philo %d\n", id);
	reset_infos(&table->philos[id], id);
	if (id % 2 == 0)
		table->philos[id].fork = 1;
	if (pthread_create(&table->philos[id].th, NULL, &set_actions, (void *) table) != 0)
	{
		perror("creation thread");
		return (0);
	}
	return (1);
}

void	join_philos(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		if (pthread_join(table->philos[count].th, NULL))
		{
			perror("join thread");
			return ;
		}
		count ++;
	}
}
/*
void	*set_actions(void *table_tmp)		//setactions pour t philo ;ulti access table id
{
	t_table *table = table_tmp;
	print_time(table->params->start_time);
//	while (table->end == 0)
		printf("action philo %d\n", table->id);
	return(NULL);
}
*/
void	*set_actions(void *table_tmp)
{
	t_table	*table;
	//t_philo *philo;
	int	id;

	table = table_tmp;
	id = table->id;
	//philo = &table->philos[id];
	while (table->end == 0)
	{
	//	printf("action philo %d\n", table->philos[id].id);
		if (table->philos[id].fork == 1)
		{
			set_infos(table, 0, true);		// fork
			set_infos(table, 1, true);			// eat
			usleep(table->params->eat_time * 1000);		
			set_infos(table, 1, false);
			set_infos(table, 0, false);		// fork
			table->philos[id].last_meal = get_time(table->params->start_time);
			set_infos(table, 4, false);		// last meal
			set_infos(table, 2, true);		// sleep
			usleep(table->params->sleep_time * 1000);
			set_infos(table, 2, false);
			set_infos(table, 3, true);		//think
		}
		else
			table->philos[id].think = true;
		if (table->philos[id].meals >= table->params->max_meals)
			table->satisfied ++;
	}
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
	if (id == table->params->nb_philo - 1)
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
	if (state && table->end == 0)
		print_infos(&table->philos[id], table->params->start_time);
}

void	reset_infos(t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->fork = false;
	philo->alive = true;
	philo->meals = 0;
	philo->last_meal = 0;
}
