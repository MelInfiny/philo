#include "philo.h"

void	reset_infos(t_philo *philo, int id)
{
	pthread_mutex_lock(philo->pprint);
	philo->th = 0;
	philo->id = id + 1;
	philo->start = false;
	philo->fork = false;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->meals = 0;
	philo->last_meal = 0;
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_mutex_unlock(philo->pprint);
}

void	set_infos(t_table *table, t_philo *philo, int status, bool state)
{
	pthread_mutex_lock(philo->pprint);
	if (status == 0)
		philo->fork = state;
	else if (status == 1)
		philo->eat = state;
	else if (status == 2)
		philo->sleep = state;
	else if (status == 3)
		philo->think = state;
	if (status != 3)
		philo->think = false;
	status = table->end;
	if (status == 0 && state)
		print_infos(philo, table->params->start_time);
	pthread_mutex_unlock(philo->pprint);
}

static void	get_meal(t_table *table, t_philo *philo, int prec)
{
	unsigned int	meals;

	if (get_fork(table, philo, prec) == 0)
		return ;
	set_infos(table, philo, 0, false);
	set_infos(table, philo, 1, true);		// eat
	get_last_meal(table, philo, 1);
	usleep(table->params->eat_time * 1000);	
	set_infos(table, philo, 1, false);
	set_infos(table, philo, 2, true);		// sleep
	//pthread_mutex_unlock(&philo->mutex);
	//pthread_mutex_unlock(&table->philos[prec].mutex);
	set_infos(table, &table->philos[prec], 0, false);
	meals = set_meal(philo, 1) + 1;
	usleep(table->params->sleep_time * 1000);
	set_infos(table, philo, 2, false);
	set_infos(table, philo, 3, true);		//think
	if (table->params->max_meals > 0 && meals == table->params->max_meals)
		get_satisfied(table, philo, 1);
}

int	get_fork(t_table *table, t_philo *philo, int prec)
{

	if (set_fork(philo, -1))
		return (0);
	set_fork(&table->philos[prec], 1);
	set_infos(table, philo, 0, true);		// fork
	/*own = pthread_mutex_lock(&philo->mutex);
	if (!own)
	{
		left = pthread_mutex_lock(&table->philos[prec].mutex);
		{
			if (!left)
			{
				set_infos(table, philo, 0, true);		// fork
				return (1);
			}
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	*/
	return (1);
}

void	*set_actions(void *table_tmp)
{
	t_table	*table;
	t_philo *philo;
	unsigned int	prec;
	
	table = table_tmp;
	philo = &table->philos[get_id(table, 0)];
	prec = get_prec(table, philo);
	if (prec + 1 == philo->id)
	{
		set_infos(table, philo, 0, true);
		usleep(table->params->die_time);
		return (NULL);
	}
	if (!philo->start)
		usleep(1500);
	while (get_alive(philo, 2))
	{
		get_meal(table, philo, prec);
		usleep(100);
	}
	return (NULL);
}
