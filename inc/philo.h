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
	pthread_mutex_t		mutex;
	bool			fork;
	bool			eat;
	bool			sleep;
	bool			think;
	bool			alive;
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

void	free_table(t_table *table);
void	ft_putstr_fd(int fd, char *s);
void	*ft_calloc(size_t n, size_t size_of);

unsigned long	get_start_time(void);
unsigned long	get_time(unsigned long start);

int	init_philo(t_table *table);
int	get_prec(t_table *table, t_philo *philo);
int	get_next(t_table *table, t_philo *philo);
void	create_philos(t_table *table);
void	join_philos(t_table *table);
void	*check_alive(void *table);

void	set_infos(t_table *table, t_philo *philo, int status, bool state);
void	print_infos(t_philo *philo, unsigned long time);
void	reset_infos(t_philo *philo, int id);
void	*set_actions(void *table);

void	get_meal(t_table *table, t_philo *philo);
int	is_available(t_table *table, t_philo *philo);
#endif
