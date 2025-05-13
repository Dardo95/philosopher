/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:16:17 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/13 16:32:10 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_config(t_config *cfg)
{
	int	i;
	cfg->philos_full = 0;
	pthread_mutex_init(&cfg->full_mutex, NULL);
	cfg->stop = 0;
	cfg->forks = malloc(cfg->n_philos * sizeof(pthread_mutex_t));
	if (!cfg->forks)
		return (0);
	i = 0;
	while (i < cfg->n_philos)
	{
		if (pthread_mutex_init(&cfg->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	cfg->philos = malloc(cfg->n_philos * sizeof(t_philo));
	if (!cfg->philos)
		return (0);
	if (pthread_mutex_init(&cfg->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&cfg->stop_mutex, NULL) != 0)
		return (0);
	cfg->first_timestamp = get_now_ms();
	return (1);
}

int	init_philosophers(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < cfg->n_philos)
	{
		cfg->philos[i].id = i + 1;
		cfg->philos[i].meals = 0;
		cfg->philos[i].last_meal = get_now_ms();
		cfg->philos[i].cfg = cfg;
		cfg->philos[i].left_fork = &cfg->forks[i];
		cfg->philos[i].right_fork = &cfg->forks[(i + 1) % cfg->n_philos];
		if (pthread_mutex_init(&cfg->philos[i].last_meal_mutex, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
