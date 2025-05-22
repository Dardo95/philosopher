/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:11:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/22 19:05:24 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->cfg->n_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		usleep(philo->cfg->time_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->cfg->time_eat * 1000 / 2);
	else
		usleep(philo->cfg->time_eat * 1000 / 3);
	while (!simulation_stopped(philo->cfg))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n_philos)
	{
		if (pthread_create(&cfg->philos[i].thread, NULL, routine,
				&cfg->philos[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	wait_for_threads(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n_philos)
	{
		if (pthread_join(cfg->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	simulation_stopped(t_config *cfg)
{
	int	stopped;

	pthread_mutex_lock(&cfg->stop_mutex);
	stopped = cfg->stop;
	pthread_mutex_unlock(&cfg->stop_mutex);
	return (stopped);
}
