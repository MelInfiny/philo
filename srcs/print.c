#include "philo.h"

void	print_time(unsigned int start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf("%ld ms : ", time.tv_usec - start);
}

unsigned int	get_time()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec);
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
	else
		printf("%d is thinking\n", philo->id);
	return (NULL);
}
