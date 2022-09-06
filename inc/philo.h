#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table {
	unsigned int	nb_philo;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	max_meals;
}	t_table;

typedef	struct s_philo {
	pthread_t	th;
	bool		fork;
	bool		eat;
	bool		sleep;
	bool		think;
	bool		alive;
	int		id;
	int		meals;
}			t_philo;

// ***************** PARSING ********************
// **********************************************

t_table	*ft_parser(int ac, char **argv);

void	ft_putstr_fd(int fd, char *s);

void	*ft_calloc(size_t n, size_t size_of);

t_philo	*create_philos(t_table *table);
void	print_time(void);
void	*print_infos(void *philo);
void	set_infos(t_philo *philo, int status, bool state);

void	init_philo(t_table *table, t_philo *philo, int id);
void	*tmp(void *philo);
void	*monitoring_philos(void *table);
#endif
