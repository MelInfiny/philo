#include "philo.h"

static void	free_mutex(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		pthread_mutex_unlock(&table->philos[count].mutex);
		pthread_mutex_destroy(&table->philos[count].mutex);
		count ++;
	}
}

void	free_thread(t_table *table)
{
	int	count;

	count = 0;
	while (count < table->params->nb_philo)
	{
		pthread_detach(table->philos[count].th);
		count ++;
	}
}

void	free_table(t_table *table)
{
	free_mutex(table);
	free(table->philos);
	free(table->params);
	free(table);
}

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
