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
	int		satisfied;
	int		id;
	int		end;	
}			t_table;

// ***************** PARSING ********************
// **********************************************

t_param	*ft_parser(int ac, char **argv);

void	ft_putstr_fd(int fd, char *s);

void	*ft_calloc(size_t n, size_t size_of);

void	create_philos(t_table *table);

//int	init_philo(t_param *params, t_philo *philo, int id);
int	init_philo(t_table *table);
int	is_available(t_table *table);
unsigned long	get_start_time(void);
unsigned long	get_time(unsigned long start);

void	philosophers(t_table *table);
void	join_philos(t_table *table);
void	set_infos(t_table *table, int status, bool state);
void	print_time(unsigned long start);

void	print_infos(t_philo *philo, unsigned long time);
void	*tmp(void *philo);
void	*monitor(void *table);
void	*check_alive(void *table);
void	*set_actions(void *table);

void	reset_infos(t_table *table);
void	check_table(t_table *table);
void	free_table(t_table *table);
#endif
