/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:26:22 by enolbas           #+#    #+#             */
/*   Updated: 2022/02/11 16:08:32 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

void	ft_putnbr_base_u(unsigned int nbr, const char *base);
int		ft_nbrlen_base_u(unsigned int nbr, int base);
int		print_perc(void);
int		print_nbr_u(va_list args);
int		print_nbr(va_list args);
int		print_str(va_list args);
int		print_ptr(va_list args);
int		print_char(va_list args);
int		print_hexa(va_list args, int status);
int		ft_printf(const char *format, ...);
#endif
