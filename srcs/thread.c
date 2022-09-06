#include "philo.h"

void	print_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms : ", time.tv_usec);
}

void	set_infos(t_philo *philo, int status, bool state)
{
	if (status == 0)
		philo->fork = state;
	else if (status == 1)
		philo->eat = state;
	else if (status == 2)
		philo->sleep = state;
	else if (status == 3)
		philo->think = state;
	else if (status == 4)
		philo->meals ++;
	else
		philo->alive = false;
}

void	*print_infos(void *philo_tmp)
{
	t_philo	*philo;

	philo = philo_tmp;
	if (philo->fork)
		printf("%d has taken a fork\n", philo->id);
	else if (philo->eat)
		printf("%d is eating\n", philo->id);
	else if (philo->sleep)
		printf("%d is sleeping\n", philo->id);
	else if (philo->think)
		printf("%d is thinking\n", philo->id);
	else
		printf("%d is doing nothing\n", philo->id);
	return (NULL);
}

void	*tmp(void *philo)
{
	struct timeval	time;
	
	t_philo	*p = philo;
	gettimeofday(&time, NULL);
	printf("%ld ms : new philo %d\n", time.tv_usec, p->id);
	sleep(1);
	return (NULL);
}

void	init_philo(t_table *table, t_philo *philo, int i)
{
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->fork = false;
	philo->meals = 0;
	philo->id = i + 1;
	if (pthread_create(&philo->th, NULL, &print_infos, (void *) philo) != 0)
	{
		perror("creation thread");
		free(table);
		exit(1);
	}
	pthread_join(philo->th, NULL);
}

void	*monitoring_philos(void *table_tmp)
{
	t_philo		*philos;

	philos = create_philos((t_table *)table_tmp);
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
	return (0);
}
