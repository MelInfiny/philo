#include "philo.h"

void	print_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms : ", time.tv_usec);
}

void	set_infos(t_philo *philo, int status)
{
	if (status == 0)
		philo->fork = true;
	if (status == 1)
		philo->eat = true;
	if (status == 2)
		philo->sleep = true;
	if (status == 3)
		philo->think = true;
	else
		philo->alive = false;
}

void	print_infos(t_philo *philo, int status)
{
	if (status == 0)
		printf("%d has taken a fork\n", philo->id);
	if (status == 1)
		printf("%d is eating\n", philo->id);
	else if (status == 2)
		printf("%d is sleeping\n", philo->id);
	else if (status == 3)
		printf("%d is thinking\n", philo->id);
	else
		printf("%d is dead\n", philo->id);
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

void	init_philo(t_philo *philo, int i)
{
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->fork = false;
	philo->meals = 0;
	philo->id = i + 1;
	pthread_create(&philo->th, NULL, &tmp, (void *) philo);
	pthread_join(philo->th, NULL);
}

void	*monitoring_philos()
{
	size_t		count;
	t_philo		*philoss;
	size_t		nb_philos = 4;

	philoss = (t_philo *) calloc(nb_philos, sizeof(t_philo));
	if (!philoss)
		exit(1);
	count = 0;
	while (count < nb_philos)
	{
		printf("init ...");
		init_philo(&philoss[count], count);
		count ++;
	}
	free(philoss);
	return (NULL);
}

int	main(void)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &monitoring_philos, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
