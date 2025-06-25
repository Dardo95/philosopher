/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:11:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/25 13:25:42 by enogueir         ###   ########.fr       */
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
	if (philo->cfg->n_philos % 2)
		usleep(100);
	while (run_simulation(philo->cfg))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	run_simulation(t_config *cfg)
{
	pthread_mutex_lock(&cfg->run_mutex);
	if (!cfg->running)
	{
		pthread_mutex_unlock(&cfg->run_mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&cfg->run_mutex);
	return (TRUE);
}
