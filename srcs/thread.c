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
		if (count % 2 == 0 && count != table->params->nb_philo -1)
			table->philos[count].start = true;
		count ++;
	}
}

static void	philosophers(t_table *table)
{
	philos(table);
	if (pthread_create(&table->monitor, NULL, &check_alive, (void *) table))
	{
		free_table(table);
		exit(1) ;
	}
	create_philos(table);
	printf("monitor \n");
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
		printf("main \n");
		free_table(table);
	}
	else
		free(params);
	return (0);
}
