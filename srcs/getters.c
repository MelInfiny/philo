#include "philo.h"

int	get_eat(t_philo *philo, int status)
{
	int	res;

	res = philo->eat;
	pthread_mutex_lock(philo->pprint);
	if (status == 1)
		philo->eat = true;
	else if (status == 0)
		philo->eat = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_end(t_table *table, t_philo *philo, int status)
{
	int	res;

	res = table->end;
	if (philo == NULL)
		pthread_mutex_lock(&table->print);
	else
		pthread_mutex_lock(philo->pprint);
	table->end = status;
	if (status == -1)
		printf("END : Each philosoph ils satisfied\n");
	else if (status > 0)
		printf("%ld ms : %d is died\n", get_time(table->params->start_time),table->end);
	pthread_mutex_unlock(&table->print);
	return (res);
}

int	get_alive(t_philo *philo, int status)
{
	int	res;

	res = philo->alive;
	pthread_mutex_lock(philo->pprint);
	if (status == 1)
		philo->alive = true;
	else if (status == 0)
		philo->alive = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_satisfied(t_table *table, t_philo *philo, int status)
{
	int	res;

	res = table->satisfied;
	if (philo == NULL)
		pthread_mutex_lock(&table->print);
	else
		pthread_mutex_lock(philo->pprint);
	if (status == 1)
		table->satisfied ++;
	pthread_mutex_unlock(&table->print);
	return (res);
}

int	get_last_meal(t_table *table, t_philo *philo, int status)
{
	int	res;

	res = philo->last_meal;
	pthread_mutex_lock(philo->pprint);
	if (status == 1)
		philo->last_meal = get_time(table->params->start_time);
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	set_meal(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->meals;
	if (status)
		philo->meals ++;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	set_fork(t_philo *philo, int status)
{	
	int	res;

	res = philo->fork;
	pthread_mutex_lock(philo->pprint);
	if (status == 1)
		philo->fork = true;
	else if (status == 0)
		philo->fork = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}
