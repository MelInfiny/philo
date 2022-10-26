/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:59:16 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:09:32 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen_base_u(unsigned int nbr, int base)
{
	unsigned int	count;
	unsigned int	len;

	len = (unsigned int) base;
	count = 0;
	if (nbr == 0)
		count ++;
	while (nbr)
	{
		nbr /= len;
		count ++;
	}
	return (count);
}
