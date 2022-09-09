#include "philo.h"

void	philosophers(t_table *table)
{
	pthread_t	monitor;

	create_philos(table);
	table->id = 0;
	pthread_create(&monitor, NULL, &check_alive, (void *) table);
	join_philos(table);
	pthread_join(monitor, NULL);
	printf("monitor \n");
}	

void	create_philos(t_table *table)
{
	int		count;

	table->philos = (t_philo *) calloc(table->params->nb_philo, sizeof(t_philo));
	if (!table->philos)
	{
		perror("allocation philos");
		free_table(table);
	}
	count = 0;
	table->params->start_time = get_start_time();
	while (count < table->params->nb_philo)
	{
	//	print_time(table->params->start_time);
		table->philos[count].id = count;
		if (!init_philo(table))
			pthread_exit(NULL);
		count ++;
	}

}

int	main(int ac, char **argv)
{
	t_table		*table;

	table = (t_table *) calloc(1, sizeof(t_table));
	if (!table)
		return (0);
	table->params = ft_parser(ac, argv);
	table->satisfied = 0;
	table->end = 0;
	table->id = -1;
	philosophers(table);
	printf("main \n");
	free_table(table);
	return (0);
}
