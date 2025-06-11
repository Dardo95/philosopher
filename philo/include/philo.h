/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:32 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/27 14:35:32 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE	1
# define FALSE	0

typedef struct s_philo
{
	int				id;
	int				meals;
	unsigned long	last_meal;
	int				is_finished;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	struct s_config	*cfg;
}					t_philo;

typedef struct s_config
{
	unsigned int	n_philos;
	unsigned long	time_die;
	unsigned long	time_eat;
	unsigned long	time_sleep;
	int				must_eat;
	unsigned long	first_timestamp;
	int				running;
	pthread_mutex_t	run_mutex;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}					t_config;

int					is_str_digit(char *s);
int					safe_atoi(const char *str, int *values);
int					convert_args(char **argv, int argc, int *values);
int					parse_args(int argc, char **argv, t_config *cfg);
int					init_config(t_config *cfg);
int					init_philosophers(t_config *cfg);
int 				start_simulation(t_config *cfg, pthread_t *checker);
void 				wait_for_threads(t_config *cfg, pthread_t checker);
void				*routine(void *arg);
int	run_simulation(t_config *cfg);
void *checker_routine(void *arg);
int	check_death(t_config *cfg, t_philo *philo);
void	stop_simulation_run(t_config *cfg);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
unsigned long	get_timestamp_ms(t_config *cfg);
unsigned long	get_now_ms(void);
void	print_status(t_philo *philo, const char *msg);
void free_and_destroy(t_config	*cfg);
int  philo_full_eat(t_config *cfg, t_philo *philo, int *philos_full);

#endif
