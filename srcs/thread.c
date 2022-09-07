#include "philo.h"

void	check_table(t_table *table)
{
	if (table->end == 0)
		return ;
	if (table->end == -1)
	{
		printf("END : Each philosoph is satisfied\n");
	}
	if (table->end > 0)
	{
		printf("%ld ms %d is died\n", get_time(), table->philos[table->end].id);
	}
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;
	int	satisfied;

	table = table_tmp;
	count = 0;
	satisfied = 0;
	while (count < table->params->nb_philo)
	{
		if (table->philos[count].last_meal + table->params->die_time >= get_time() && table->philos[count].eat == false)
		{
			table->philos[count].alive = false;
			table->end = count;
			break;
		}
		if (table->philos[count].meals >= table->params->max_meals)
			satisfied ++;
		count ++;
	}
	if (satisfied >= table->params->nb_philo)
		table->end = -1;
	check_table(table);
	return (NULL);
}

void	philosophers(t_table *table)
{
	pthread_t	monitor;

	table->philos = create_philos(table->params);
	pthread_create(&monitor, NULL, &check_alive, (void *) table);
	pthread_join(monitor, NULL);
	printf("monitor \n");
}	

t_philo	*create_philos(t_param *params)
{
	int	count;
	t_philo	*philos;

	philos = (t_philo *) calloc(params->nb_philo, sizeof(t_philo));
	if (!philos)
	{
		perror("allocation philos");
		free(params);
		exit(1);
	}
	count = 0;
	params->start_time = get_time();
	while (count < params->nb_philo)
	{
		print_time(params->start_time);
		if (!init_philo(params, &philos[count], count))
			pthread_exit(NULL);
		usleep(1);
		count ++;
	}
	return (philos);
}

int	main(int ac, char **argv)
{
	t_table		*table;

	table = (t_table *) calloc(1, sizeof(t_table));
	if (!table)
		return (0);
	table->params = ft_parser(ac, argv);
	philosophers(table);
	printf("main \n");
	free_table(table);
	return (0);
}
