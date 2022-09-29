#include "philo.h"

int	get_eat(t_philo *philo, int status)
{
	int	res;

	res = philo->eat;
	if (pthread_mutex_lock(philo->pprint))
		return (-1);
	if (status == 1)
		philo->eat = true;
	else if (status == 0)
		philo->eat = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_end(t_table *table, int status)
{
	int	res;

	res = table->end;
	if (pthread_mutex_lock(philo->pprint))
		return (-1);
	if (status != 0)
		table->end = status;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	get_alive(t_philo *philo, int status)
{
	int	res;

	res = philo->alive;
	if (pthread_mutex_lock(philo->pprint))
		return (-1);
	if (status == 1)
		philo->alive = true;
	else if (status == 0)
		philo->alive = false;
	pthread_mutex_unlock(philo->pprint);
	return (philo->alive);
}

int	get_satisfied(t_table *table, int status)
{
	int	res;

	res = table->satisfied;
	if (pthread_mutex_lock(philo->pprint))
		return (-1);
	if (status == 1)
		table->satisfied ++;
	pthread_mutex_unlock(philo->pprint);
	return (table->satisfied);
}

int	get_last_meal(t_table *table, t_philo *philo, int status)
{
	int	res;

	res = philo->last_meal;
	if (pthread_mutex_lock(philo->pprint))
		return (-1);
	if (status == 1)
		philo->last_meal = get_time(table->params->start_time);
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	set_fork(t_philo *philo, int status)
{	
	int	res;

	res = philo->fork;
	if (pthread_mutex_lock(philo->pprint))
		return (-1);
	if (status == 1)
		philo->fork = true;
	else if (status == 0)
		philo->fork = false;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}
