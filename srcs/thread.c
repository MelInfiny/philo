#include "philo.h"

static void	philosophers(t_table *table)
{
	pthread_t	monitor;

	table->id = 0;
	table->philos = (t_philo *) calloc(table->params->nb_philo, sizeof(t_philo));
	if (!table->philos)
	{
		perror("Allocation philos ");
		free_table(table);
	}
	pthread_create(&monitor, NULL, &check_alive, (void *) table);
	create_philos(table);
	printf("monitor \n");
	//detach_philos(table);
	pthread_join(monitor, NULL);
	join_philos(table);
	//pthread_detach(monitor);
}

int	main(int ac, char **argv)
{
	t_table		*table;
	t_param		*params;

	params = ft_parser(ac, argv);
	table = (t_table *) calloc(1, sizeof(t_table));
	if (!table)
		return (0);
	table->params = params;
	table->satisfied = 0;
	table->created = 0;
	table->end = 0;
	philosophers(table);
	printf("main \n");
	free_table(table);
	return (0);
}
