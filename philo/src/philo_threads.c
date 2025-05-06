/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:11:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/06 13:32:59 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("filosofo %d ha comenzado su hilo\n", philo->id);
	return (NULL);
}

int	start_simulation(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->n_philos)
	{
		if (pthread_create(&config->philos[i].thread, NULL, routine, &config->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	wait_for_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->n_philos)
	{
		if(pthread_join(config->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(), philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(), philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);

	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d is eating\n", get_timestamp_ms(), philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);

	philo->last_meal = get_timestamp_ms();
	philo->meals++;

	usleep(philo->config->time_eat * 1000);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	
}