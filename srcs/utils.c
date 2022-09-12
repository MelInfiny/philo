#include "philo.h"

void	free_table(t_table *table)
{
	free(table->philos);
	free(table->params);
	free(table);
	exit(1);
}

void	ft_putstr_fd(int fd, char *s)
{
	while (*s)
	{
		write(fd, &(*s++), 1);
	}
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
