/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:11:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/13 18:44:26 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(40);
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
