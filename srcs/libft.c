/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:22:17 by enolbas           #+#    #+#             */
/*   Updated: 2022/10/26 18:22:15 by enolbas          ###   ########.fr       */
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

// time = 510 ; div = time / 100 * usleep(100) + usleep(time % 100)
void	ft_usleep(t_table *table, size_t time)
{
	unsigned int	div;
	unsigned int	newtime;
	
	if (time > 10000)
		div = time / 10000;
	else if (time > 1000)
		div = time / 1000;
	else
		div = time - 1;
	newtime = div;
	while (newtime < time)
	{
		if (set_end(table, NULL, -2) > 0)
			return ;
		usleep(newtime * 1000);
		newtime += newtime * div;
	}
	usleep(time % div);
}
