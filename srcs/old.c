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