/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:14:47 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:04:12 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putnbr_base_u(unsigned int nbr, const char *base)
{
	unsigned int	len;
	char			c;

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
		ft_putnbr_base_u(nbr / len, base);
		ft_putnbr_base_u(nbr % len, base);
	}
}
