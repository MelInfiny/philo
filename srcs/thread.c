#include "philo.h"

void	check_eat(t_table *table, t_philo *philos)
{
	size_t	count;
	int	res;

	res = 1;
	count = 0;
	while (count < table->nb_philo)
	{
		if (philos[count].meals < table->max_meals)
			res = 0;
		count ++;
	}
	if (res == 1)
	{
		
		printf("END : Each philosoph is satisfied\n");
		free(philos);
		pthread_exit(NULL);
	}
}

void	*monitoring_philos(void *table_tmp)
{
	t_philo		*philos;

	philos = create_philos((t_table *) table_tmp);
	check_eat((t_table *) table_tmp, philos);
	printf("monitor end\n");
	free(philos);
	return (NULL);
}	

t_philo	*create_philos(t_table *table)
{
	size_t		count;
	t_philo		*philoss;

	philoss = (t_philo *) calloc(table->nb_philo, sizeof(t_philo));
	if (!philoss)
	{
		perror("allocation philoss");
		free(table);
		exit(1);
	}
	count = 0;
	while (count < table->nb_philo)
	{
		print_time();
		init_philo(table, &philoss[count], count);
		usleep(1);
		count ++;
	}
	return (philoss);
}

int	main(int ac, char **argv)
{
	pthread_t	monitor;
	t_table		*table;

	table = ft_parser(ac, argv);
	pthread_create(&monitor, NULL, &monitoring_philos, (void *) table);
	pthread_join(monitor, NULL);
	printf("main end\n");
	free(table);
	return (0);
}
