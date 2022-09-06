#include "philo.h"

static void	print_table(t_table *table)
{
	printf("nb_philosophers : %d\n", table->nb_philo);
	printf("time_to_eat : %d\n", table->eat_time);
	printf("time_to_die : %d\n", table->die_time);
	printf("time_to_sleep : %d\n", table->sleep_time);
	if (table->max_meals)
		printf("max meals : %d\n", table->max_meals);
}

static void	error_parsing(int error, t_table *table)
{
	if (error == 1)
		ft_putstr_fd(2, "Error : Invalid number of arguments\n");
	if (error == 2)
		ft_putstr_fd(2, ": Invalid format of arguments\n");
	ft_putstr_fd(2, "usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat\n");
	free(table);
	exit(1);
}

static int	ft_atoi(char *s, int *sign)
{
	int		count;
	long	num;

	count = 0;
	*sign = 1;
	num = 0;
	if (s[count] == 32 || (s[count] >= 9 && s[count] <= 13))
		count++;
	if (s[count] == '+' || s[count] == '-')
	{
		if (s[count] == '-')
			*sign *= -1;
		count++;
	}
	while (s[count])
	{
		num = (num * 10) + s[count] - 48;
		if (num * *sign > 2147483647 || num * *sign < -2147483648
				|| s[count] < '0' || s[count] > '9') 
			*sign = 0;
		count++;
	}
	return (num * *sign);
}

static unsigned int	check_int(char *s, t_table *table)
{
	int	sign;
	int	nbr;

	sign = 1;
	nbr = ft_atoi(s, &sign);
	if (sign == 0 || nbr < 0)
	{
		ft_putstr_fd(2, s);
		error_parsing(2, table);
	}
	return ((unsigned int) nbr);
}

t_table	*ft_parser(int ac, char **argv)
{
	t_table	*table;

	table = (t_table *) calloc (1, sizeof(t_table));
	if (!table)
		exit(1);
	if (ac < 5 || ac > 6)
		error_parsing(1, table);
	table->nb_philo = check_int(argv[1], table);
	table->die_time = check_int(argv[2], table);
	table->eat_time = check_int(argv[3], table);
	table->sleep_time = check_int(argv[4], table);
	if (ac == 6)
		table->max_meals = check_int(argv[5], table);
	else	
		table->max_meals = 0;
	print_table(table);
	return (table);
}
