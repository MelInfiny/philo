#include "philo.h"

static void	free_mutex(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		pthread_mutex_destroy(&table->philos[count].mutex);
		count ++;
	}
	pthread_mutex_destroy(&table->print);
}

void	free_table(t_table *table)
{
	free_mutex(table);
	free(table->philos);
	free(table->params);
	free(table);
}

void	error_philo(t_table *table, char *msg)
{
	perror(msg);
	kill_philos(table);
	return ;
}

void	kill_philos(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		table->philos[count].alive = false;
		count ++;
	}
}

void	kill_philo(t_philo *philo)
{
	philo->alive = false;
//	if (!pthread_mutex_unlock(&philo->mutex))
//		pthread_mutex_destroy(&philo->mutex);
}
