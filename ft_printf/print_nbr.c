/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:58:13 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:09:15 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	ft_putnbr(int nbr)
{
	unsigned int	tmp;
	char			c;

	if (nbr < 0)
	{
		write(1, "-", 1);
		if (nbr == -2147483648)
		{
			write(1, "2147483648", 10);
			return ;
		}
		nbr *= -1;
	}
	tmp = (unsigned int) nbr;
	if (tmp > 9)
	{
		ft_putnbr(tmp / 10);
		ft_putnbr(tmp % 10);
	}
	else
	{
		c = tmp + '0';
		write(1, &c, 1);
	}
}

static int	ft_nbrlen(int nbr)
{
	unsigned int	count;

	count = 0;
	if (nbr <= 0)
	{
		nbr *= -1;
		count ++;
	}
	while (nbr)
	{
		nbr /= 10;
		count ++;
	}
	return (count);
}

int	print_nbr(va_list args)
{
	int	nbr;

	nbr = va_arg(args, int);
	ft_putnbr(nbr);
	return (ft_nbrlen(nbr));
}
