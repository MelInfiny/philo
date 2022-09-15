#include "philo.h"

void	create_philos(t_table *table)
{
	int		count;
/*
	table->philos = (t_philo *) calloc(table->params->nb_philo, sizeof(t_philo));
	if (!table->philos)
	{
		perror("allocation philos");
		free_table(table);
	}
	*/
	count = 0;
	table->params->start_time = get_start_time();
	while (count < table->params->nb_philo)
	{
		table->id = count;
		if (!init_philo(table))
			return ;
		count ++;
	}
}

int	init_philo(t_table *table)
{
	int	id;

	id = table->id;
	reset_infos(&table->philos[id], table->id);
	table->created ++;
	if (id % 2 == 0 && id != table->params->nb_philo -1)
	{
		table->philos[id].start = true;
		printf("starter %d\n", table->philos[id].id);
	}
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

int	get_prec(t_table *table, t_philo *philo)
{
	int	id;
	int	prec;

	id = philo->id - 1;
	if (id == 0)
		prec = table->params->nb_philo - 1;
	else
		prec = id - 1;
	return (prec);
}

void	reset_infos(t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->start = false;
	philo->fork = false;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->meals = 0;
	philo->last_meal = 0;
	pthread_mutex_init(&philo->mutex, NULL);
}
