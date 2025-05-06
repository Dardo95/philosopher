/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:32 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/06 13:30:52 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_config
{
	int				n_philos;
	int 			time_die;
	int 			time_eat;
	int 			time_sleep;
	int 			must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t write_lock;
	struct  s_philo	*philos;
}	t_config;

typedef	struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_config		*config;
}	t_philo;

int		is_str_digit(char *s);
int		safe_atoi(const char *str, int *values);
int		convert_args(char **argv, int argc, int *values);
int		parse_args(int argc, char **argv, t_config *config);
int		init_config(t_config *config);
int		init_philosophers(t_config *config);
void	*routine(void *arg);
int		start_simulation(t_config *config);
int		wait_for_threads(t_config *config);
void	philo_eat(t_philo *philo);

#endif
