#include "philo.h"

static void	init_table(t_table *table, t_param *params)
{
	table->monitor = 0;
	table->params = params;
	table->satisfied = 0;
	table->end = 0;
	table->id = 0;
	pthread_mutex_init(&table->print, NULL);
}

static void	philosophers(t_table *table)
{
	create_philos(table);
	if (pthread_create(&table->monitor, NULL, &check_alive, (void *) table))
	{
		free_table(table);
		exit(1) ;
	}
	if (table->params->nb_philo == 1)
		set_infos(table, &table->philos[0], 0, true);
	else
		init_philos(table);
	pthread_join(table->monitor, NULL);
	join_philos(table);
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
		free_table(table);
	}
	else
		free(params);
	return (0);
}
