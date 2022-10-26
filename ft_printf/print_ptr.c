/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:06:41 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 13:21:41 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_ul(unsigned long long nbr, const char *base)
{
	unsigned long long	len;
	char				c;

	len = 0;
	while (base[len])
		len ++;
	if (nbr < len)
	{
		c = base[nbr];
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr_ul(nbr / len, base);
		ft_putnbr_ul(nbr % len, base);
	}
}

static int	ft_nbrlen_ul(unsigned long long ptr, unsigned long long base)
{
	unsigned long long	count;

	count = 0;
	if (ptr == 0)
		count ++;
	while (ptr)
	{
		ptr /= base;
		count++;
	}
	return (count);
}

int	print_ptr(va_list args)
{
	long long	ptr;
	int			len;

	ptr = va_arg(args, unsigned long long);
	if (ptr >= 0)
	{
		len = 2;
		write(1, "0x", len);
		ft_putnbr_ul(ptr, "0123456789abcdef");
		len += ft_nbrlen_ul(ptr, 16);
	}
	else
	{
		len = 5;
		write(1, "(nil)", len);
	}
	return (len);
}
