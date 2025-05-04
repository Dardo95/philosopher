/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:16:17 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/04 18:55:50 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_config(t_config *config)
{
	config->forks = malloc(config->n_philos * sizeof(pthread_mutex_t));
	if (!config->forks)
		return (0);
	config->philos = malloc(config->n_philos * sizeof(t_philo));
	if (!config->philos)
		return (0);
	if (pthread_mutex_init(&config->write_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_philosophers(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->n_philos)
	{
		config->philos[i].id = i + 1;
		config->philos[i].meals = 0;
		config->philos[i].last_meal = 0;
		config->philos[i].config = config;
		config->philos[i].left_fork = &config->forks[i];
		config->philos[i].right_fork = &config->forks[(i + 1) % config->n_philos];
		i++;
	}
	return (1);
}