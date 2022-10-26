/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:15:43 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:07:49 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	switch_format(va_list args, char format)
{
	int	res;

	res = 5;
	if (format == '%')
		res = print_perc();
	else if (format == 'c')
		res = print_char(args);
	else if (format == 'd' || format == 'i')
		res = print_nbr(args);
	else if (format == 'x')
		res = print_hexa(args, 1);
	else if (format == 'X')
		res = print_hexa(args, 0);
	else if (format == 'u')
		res = print_nbr_u(args);
	else if (format == 'p')
		res = print_ptr(args);
	else if (format == 's')
		res = print_str(args);
	else
		write(1, "error", 5);
	return (res);
}

int	ft_printf(const char *str, ...)
{
	va_list	all_args;
	size_t	nb_print;
	size_t	count;

	va_start(all_args, str);
	nb_print = 0;
	count = 0;
	while (str[count])
	{
		if (str[count] == '%')
		{
			count ++;
			nb_print += switch_format(all_args, str[count]);
		}
		else
		{
			write(1, &str[count], 1);
			nb_print++;
		}
		count ++;
	}
	return (nb_print);
}
