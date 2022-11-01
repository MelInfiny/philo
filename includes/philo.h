/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enolbas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:52:30 by enolbas           #+#    #+#             */
/*   Updated: 2022/11/01 16:26:39 by enolbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

// ****************** STRUCTURES *********************//
// ***************************************************//
typedef struct s_param {
	int				nb_philo;
	unsigned int	die_time;
	unsigned int	eat_time;
	unsigned int	sleep_time;
	unsigned int	max_meals;
	unsigned long	start_time;
}	t_param;

typedef struct s_philo {
	pthread_t			th;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*pprint;
	bool				start;
	bool				fork;
	bool				eat;
	bool				sleep;
	bool				think;
	bool				alive;
	int					meals;
	unsigned int		id;
	unsigned long		last_meal;
	struct s_philo		*prec;
	t_param				*params;
}	t_philo;

typedef struct s_table {
	pthread_mutex_t	print;
	pthread_t		monitor;
	t_param			*params;
	t_philo			*philos;
	int				satisfied;
	int				created;
	int				end;
}	t_table;

// ****************** UTILS *********************//
// **********************************************//
t_param			*ft_parser(int ac, char **argv);
void			free_table(t_table *table);
void			ft_putstr_fd(int fd, char *s);
void			*ft_calloc(size_t n, size_t size_of);
unsigned long	get_start_time(void);
unsigned long	get_time(unsigned long start);

// ***************** GETTERS ********************//
// **********************************************//
int				get_fork(t_table *table, t_philo *philo, int prec);
int				get_last_meal(t_philo *philo, int status);
int				get_eat(t_philo *philo, int status);
int				set_end(t_table *table, t_philo *philo, int status);
int				set_meal(t_philo *philo, int status);
int				set_fork(t_philo *philo, int status);
int				get_alive(t_philo *philo, int status);
int				get_created(t_table *table, int status);

// ***************** PHILOS ********************//
// **********************************************//
void			create_philos(t_table *table);
void			init_philos(t_table *table);
void			prec_philo(t_table *table);
void			join_philos(t_table *table);
void			kill_philo(t_philo *philo);
void			kill_philos(t_table *table);
void			error_philo(t_table *table, char *msg);

// ***************** THREADS ********************//
// **********************************************//
void			*check_alive(void *table);
void			*set_actions(void *philo);
void			ft_usleep(t_philo *philo, size_t time);

// ****************** INFOS *********************//
// **********************************************//
void			print_fork(t_philo *philo, int status);
void			print_infos(t_philo *philo);
void			reset_infos(t_table *table, t_philo *philo, int id);
#endif
