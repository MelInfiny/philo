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
	unsigned int	start_time;
}	t_table;

typedef	struct s_philo {
	pthread_t		th;
	bool			fork;
	bool			eat;
	bool			sleep;
	bool			think;
	bool			alive;
	unsigned int			think_time;
	unsigned int		id;
	unsigned int		meals;
}			t_philo;

// ***************** PARSING ********************
// **********************************************

t_table	*ft_parser(int ac, char **argv);

void	ft_putstr_fd(int fd, char *s);

void	*ft_calloc(size_t n, size_t size_of);

t_philo	*create_philos(t_table *table);

unsigned int	get_time(void);
void	print_time(unsigned int start);
void	*print_infos(void *philo);
void	set_infos(t_philo *philo, int status, bool state);

void	init_philo(t_table *table, t_philo *philo, int id);
void	*tmp(void *philo);
void	*monitoring_philos(void *table);

void	check_eat(t_table *table, t_philo *philos);
void	check_death(t_table *table, t_philo *philos);
#endif
