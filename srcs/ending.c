#include "philo.h"

static void	*check_end(t_table *table, int status)
{
	table->end = status;
	if (table->end == -1)
	{
		printf("END : Each philosoph is satisfied\n");
	}
	if (table->end > 0)
	{
		printf("%ld ms : %d is died\n", get_time(table->params->start_time), table->end);
	}
	kill_all_philos(table);
	return (NULL);
}

static size_t	get_start(t_table *table)
{
	size_t	min;

	min = table->params->eat_time * table->params->nb_philo;
	if (table->params->die_time < min)
		min = table->params->die_time;
	return (min);
}

static void	kill_philo(t_philo *philo)
{
	philo->alive = false;
	if (!pthread_mutex_unlock(&philo->mutex))
		pthread_mutex_destroy(&philo->mutex);
}

void	kill_all_philos(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		table->philos[count].alive = false;
		count ++;
	}
}

void	*check_alive(void *table_tmp)
{
	t_table	*table;
	int	count;

	table = table_tmp;
	while (table->created < table->params->nb_philo || get_time(table->params->start_time) < get_start(table))
		count = -1;
	//detach_philos(table);
	while (1)
	{
		if (count < table->params->nb_philo - 1)
			count ++;
		else
			count = 0;
		if (table->satisfied > 0 && table->satisfied >= table->params->nb_philo - 1)
			return (check_end(table, -1));
		if (table->philos[count].last_meal + table->params->die_time <= get_time(table->params->start_time) && table->philos[count].eat == false)
		{
			kill_philo(&table->philos[count]);
			return (check_end(table, table->philos[count].id));
		}
		usleep(200);
	}
	return (NULL);
}

