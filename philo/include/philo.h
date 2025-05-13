/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:32 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/13 14:13:33 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int				n_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				philos_full;
	pthread_mutex_t	full_mutex;
	int				stop;
	pthread_mutex_t	stop_mutex;
	long			first_timestamp;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t last_meal_mutex;
	t_config		*cfg;
}					t_philo;

int					is_str_digit(char *s);
int					safe_atoi(const char *str, int *values);
int					convert_args(char **argv, int argc, int *values);
int					parse_args(int argc, char **argv, t_config *cfg);
int					init_config(t_config *cfg);
int					init_philosophers(t_config *cfg);
void				*routine(void *arg);
void				*death_checker(void *arg);
int					check_philo_death(t_philo *philo);
int					start_simulation(t_config *cfg);
int					simulation_stopped(t_config *cfg);
int					wait_for_threads(t_config *cfg);
void				take_forks(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
long				get_now_ms(void);
long				get_timestamp_ms(t_config *cfg);

#endif
