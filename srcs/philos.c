#include "philo.h"

void	init_philo(t_table *table, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->fork = false;
	philo->meals = 0;
	if (pthread_create(&philo->th, NULL, &print_infos, (void *) philo) != 0)
	{
		perror("creation thread");
		free(table);
		exit(1);
	}
	if (pthread_join(philo->th, NULL) != 0)
	{
		perror("join thread");
		free(table);
		exit(1);
	}
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
