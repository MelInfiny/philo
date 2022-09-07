#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_param {
	int		nb_philo;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	max_meals;
	unsigned long	start_time;
}	t_param;

typedef	struct s_philo {
	pthread_t		th;
	bool			fork;
	bool			eat;
	bool			sleep;
	bool			think;
	bool			alive;
	unsigned int		think_time;
	unsigned int		id;
	unsigned int		meals;
	unsigned long		last_meal;
}			t_philo;

typedef struct s_table {
	t_param		*params;
	t_philo		*philos;
	int		count;
	int		end;	
}			t_table;

// ***************** PARSING ********************
// **********************************************

t_param	*ft_parser(int ac, char **argv);

void	ft_putstr_fd(int fd, char *s);

void	*ft_calloc(size_t n, size_t size_of);

t_philo	*create_philos(t_param *params);

int	init_philo(t_param *params, t_philo *philo, int id);
unsigned long	get_time(void);

void	philosophers(t_table *table);
void	set_infos(t_philo *philo, int status, bool state);
void	print_time(unsigned long start);

void	*print_infos(void *philo);
void	*tmp(void *philo);
void	*monitor(void *table);
void	*check_alive(void *table);

void	check_table(t_table *table);
void	free_table(t_table *table);
#endif
