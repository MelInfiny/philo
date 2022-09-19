#include "philo.h"

void	create_philos(t_table *table)
{
	int	count;

	count = 0;
	table->philos = (t_philo *) calloc(table->params->nb_philo, sizeof(t_philo));
	if (!table->philos)
	{
		perror("Allocation philos ");
		free(table->params);
		free(table);
		exit(1);
	}
	while (count < table->params->nb_philo)
	{
		reset_infos(&table->philos[count], count);
		table->philos[count].pprint = &table->print;
		if (count % 2 == 0 && count != table->params->nb_philo -1)
			table->philos[count].start = true;
		count ++;
	}
}

void	init_philos(t_table *table)
{
	int		count;

	count = 0;
	table->params->start_time = get_start_time();
	while (count < table->params->nb_philo)
	{
		table->id = count;
		if (pthread_create(&table->philos[count].th, NULL, &set_actions, (void *) table) != 0)
		{
			return (error_philo(table, "cretation thread "));
		}
		usleep(200);
		count ++;
	}
}

void	join_philos(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		if (pthread_join(table->philos[count].th, NULL))
		{
			error_philo(table, "join thread ");
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
