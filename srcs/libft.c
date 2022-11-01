/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:22:17 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/01 16:19:25 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(int fd, char *s)
{
	while (*s)
		write(fd, &(*s++), 1);
}

void	*ft_calloc(size_t n, size_t size)
{
	void		*ptr;
	size_t		max;
	size_t		count;

	count = 0;
	ptr = (void *) malloc(size * n);
	if (!ptr)
		return (NULL);
	max = n * size;
	while (count < max)
	{
		*(unsigned char *)(ptr + count) = 0;
		count++;
	}
	return (ptr);
}

void	ft_usleep(t_philo *philo, size_t time)
{
	unsigned int	div;

	div = 0;
	while ((div + 200) < time)
	{
		usleep(200 * 1000);
		div += 200;
		if (!get_alive(philo, 2))
			return ;
	}
	usleep((time - div) * 1000);
}
