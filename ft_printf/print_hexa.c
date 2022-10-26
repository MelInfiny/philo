/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:02:56 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:01:58 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	print_hexa(va_list args, int status)
{
	unsigned long	nbr;

	nbr = va_arg(args, unsigned long);
	if (status)
		ft_putnbr_base_u(nbr, "0123456789abcdef");
	else
		ft_putnbr_base_u(nbr, "0123456789ABCDEF");
	return (ft_nbrlen_base_u(nbr, 16));
}
