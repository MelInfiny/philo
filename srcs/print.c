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

unsigned long	get_start_time()
{
	struct timeval	time;
	unsigned long	mstime;
	unsigned long	stime;

	gettimeofday(&time, NULL);
	stime = time.tv_sec * 1000;
	mstime = time.tv_usec / 1000;
	return (stime + mstime);
}

unsigned long	get_time(unsigned long start)
{
	struct timeval	time;
	unsigned long	mstime;
	unsigned long	stime;

	gettimeofday(&time, NULL);
	stime = time.tv_sec * 1000;
	mstime = time.tv_usec / 1000;
	return (stime + mstime) - start;
}

void	print_infos(t_philo *philo, unsigned long time)
{
	print_time(time);
	if (philo->fork)
		printf("%d has taken a fork\n", philo->id);
	if (philo->eat)
		printf("%d is eating\n", philo->id);
	if (philo->sleep)
		printf("%d is sleeping\n", philo->id);
	if (philo->think)
		printf("%d is thinking\n", philo->id);
}
