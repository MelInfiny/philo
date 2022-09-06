#include "philo.h"

void	check_eat(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		if (table->philos[count].meals < table->params->max_meals)
			return ;
		count ++;
	}
	printf("END : Each philosoph is satisfied\n");
	free(table);
	pthread_exit(NULL);
}

void	check_death(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		if (table->philos[count].alive == false)
		{
			print_time(table->params->start_time);
			printf("%d is died\n", table->philos[count].id);
			free(table);
			pthread_exit(NULL);
		}
		count ++;
	}
}
/*
void	check_alive(void *philos)
{
	int	time;

	time = get_time();
	while (*philos)
	{
		if ((*philos).
	}
}
*/
void	*monitoring_philos(void *table_tmp)
{
//	pthread_t	isend;
	t_table		*table;

	table = (t_table *) table_tmp;
	table->philos = create_philos((t_param *) table->params);
	check_eat((t_table *) table);
	check_death((t_table *) table);
	printf("monitor \n");
	free((t_table *) table->philos);
	return (NULL);
}	

t_philo	*create_philos(t_param *params)
{
	size_t		count;
	t_philo		*philoss;

	philoss = (t_philo *) calloc(params->nb_philo, sizeof(t_philo));
	if (!philoss)
	{
		perror("allocation philoss");
		free(params);
		exit(1);
	}
	count = 0;
	params->start_time = get_time();
	while (count < params->nb_philo)
	{
		print_time(params->start_time);
		init_philo(params, &philoss[count], count);
		usleep(1);
		count ++;
	}
	return (philoss);
}

int	main(int ac, char **argv)
{
	pthread_t	monitor;
	t_table		*table;

	table = (t_table *) calloc(1, sizeof(t_table));
	if (!table)
		return (0);
	table->params = ft_parser(ac, argv);
	pthread_create(&monitor, NULL, &monitoring_philos, (void *) table);
	pthread_join(monitor, NULL);
	printf("main \n");
	free(table);
	return (0);
}
