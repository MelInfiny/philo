/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:52:05 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:05:58 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	print_str(va_list args)
{
	char	*str;
	int		len;

	len = 0;
	str = va_arg(args, char *);
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}
