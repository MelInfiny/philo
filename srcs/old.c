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


void	check_eat(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
			return ;
		count ++;
	}
	free_table(table);
}

void	check_death(t_table *table)
{
	size_t	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		if (table->philos[count].alive == false)
		{
			free_table(table);
		}
		count ++;
	}
}