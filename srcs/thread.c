#include "philo.h"

static void	init_table(t_table *table, t_param *params)
{
	table->monitor = 0;
	table->params = params;
	table->satisfied = 0;
	table->created = 0;
	table->end = 0;
	table->id = 0;
}

static void	philos(t_table *table)
{
	table->philos = (t_philo *) calloc(table->params->nb_philo, sizeof(t_philo));
	if (!table->philos)
	{
		perror("Allocation philos ");
		free(table->params);
		free(table);
		exit(1);
	}
	while (table->id < table->params->nb_philo)
	{
		reset_infos(&table->philos[table->id], table->id);
		table->id ++;
	}
	table->id = 0;
}

static void	philosophers(t_table *table)
{
	philos(table);
	pthread_create(&table->monitor, NULL, &check_alive, (void *) table);
	create_philos(table);
	printf("monitor \n");
	//detach_philos(table);
	pthread_join(table->monitor, NULL);
	join_philos(table);
	//pthread_detach(monitor);
}

int	main(int ac, char **argv)
{
	t_table		*table;
	t_param		*params;

	params = ft_parser(ac, argv);
	table = (t_table *) calloc(1, sizeof(t_table));
	if (table)
	{
		init_table(table, params);
		philosophers(table);
		printf("main \n");
		free_table(table);
	}
	else
		free(params);
	return (0);
}
