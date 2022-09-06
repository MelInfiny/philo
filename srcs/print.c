#include "philo.h"

void	print_time(unsigned long start)
{
	struct timeval	time;
	unsigned long	mstime;
	unsigned long	stime;

	gettimeofday(&time, NULL);
	stime = time.tv_sec * 1000;
	mstime = time.tv_usec / 1000;
	printf("%ld ms : ", (stime + mstime) - start);
}

unsigned long	get_time()
{
	struct timeval	time;
	unsigned long	mstime;
	unsigned long	stime;

	gettimeofday(&time, NULL);
	stime = time.tv_sec * 1000;
	mstime = time.tv_usec / 1000;
	return (stime + mstime);
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
