#include "philo.h"

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
	return ((stime + mstime) - start);
}

void	print_infos(t_philo *philo, unsigned long time)
{
	if (philo->fork)
		printf("%ld ms : %d has taken a fork\n", get_time(time), philo->id);
	if (philo->eat)
		printf("%ld ms : %d is eating\n", get_time(time), philo->id);
	if (philo->sleep)
		printf("%ld ms : %d is sleeping\n", get_time(time), philo->id);
	if (philo->think)
		printf("%ld ms : %d is thinking\n", get_time(time), philo->id);
}
