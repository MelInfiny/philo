#include "philo.h"

void	check_eat(t_table *table, t_philo *philos)
{
	size_t	count;

	count = 0;
	while (count < table->nb_philo)
	{
		if (philos[count].meals < table->max_meals)
			return ;
		count ++;
	}
	printf("END : Each philosoph is satisfied\n");
	free(philos);
	pthread_exit(NULL);
}

void	check_death(t_table *table, t_philo *philos)
{
	size_t	count;

	count = 0;
	while (count < table->nb_philo)
	{
		if (philos[count].alive == false)
		{
			print_time(table->start_time);
			printf("%d is died\n", philos[count].id);
			free(philos);
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
	t_philo		*philos;
//	pthread_t	isend;

	philos = create_philos((t_table *) table_tmp);
	check_eat((t_table *) table_tmp, philos);
	check_death((t_table *) table_tmp, philos);
	printf("monitor \n");
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
	table->start_time = get_time();
	while (count < table->nb_philo)
	{
		print_time(table->start_time);
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
	printf("main \n");
	free(table);
	return (0);
}
