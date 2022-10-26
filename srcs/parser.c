/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:21:58 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 13:54:24 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_params(t_param *params)
{
	ft_printf("nb_philosophers : %d\n", params->nb_philo);
	ft_printf("time_to_eat : %d\n", params->eat_time);
	ft_printf("time_to_die : %d\n", params->die_time);
	ft_printf("time_to_sleep : %d\n", params->sleep_time);
	if (params->max_meals)
		ft_printf("max meals : %d\n", params->max_meals);
}

static void	error_parsing(int error, t_param *params)
{
	if (error == 1)
		ft_putstr_fd(2, "Error : Invalid number of arguments\n");
	if (error == 2)
		ft_putstr_fd(2, ": Invalid format of arguments\n");
	if (error == 3)
		ft_putstr_fd(2, ": Cannot launch simulation with parameters <= 0\n");
	ft_putstr_fd(2, ": Bad input parameters\n");
	free(params);
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

static unsigned int	check_int(char *s, t_param *params)
{
	int	sign;
	int	nbr;

	sign = 1;
	nbr = ft_atoi(s, &sign);
	if (sign == 0)
	{
		ft_putstr_fd(2, s);
		error_parsing(2, params);
	}
	else if (nbr <= 0)
	{
		ft_putstr_fd(2, s);
		error_parsing(3, params);
	}
	return ((unsigned int) nbr);
}

t_param	*ft_parser(int ac, char **argv)
{
	t_param	*params;

	params = (t_param *) calloc (1, sizeof(t_param));
	if (!params)
		exit(1);
	if (ac < 5 || ac > 6)
		error_parsing(1, params);
	params->nb_philo = check_int(argv[1], params);
	params->die_time = check_int(argv[2], params);
	params->eat_time = check_int(argv[3], params);
	params->sleep_time = check_int(argv[4], params);
	if (ac == 6)
		params->max_meals = check_int(argv[5], params);
	else
		params->max_meals = 0;
	return (params);
}
