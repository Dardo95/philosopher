/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:16:17 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/27 13:54:39 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_config(t_config *cfg)
{
	int	i;

	pthread_mutex_init(&cfg->run_mutex, NULL);
	pthread_mutex_init(&cfg->write_lock, NULL);
	cfg->running = TRUE;
	cfg->forks = malloc(cfg->n_philos * sizeof(pthread_mutex_t));
	if (!cfg->forks)
		return (FALSE);
	i = 0;
	while (i < (int)cfg->n_philos)
	{
		pthread_mutex_init(&cfg->forks[i], NULL);
		i++;
	}
	cfg->philos = malloc(cfg->n_philos * sizeof(t_philo));
	if (!cfg->philos)
		return (FALSE);
	cfg->first_timestamp = get_now_ms();
	return (TRUE);
}

int	init_philosophers(t_config *cfg)
{
	int	i;

	i = 0;
	while (i < (int)cfg->n_philos)
	{
		cfg->philos[i].id = i + 1;
		cfg->philos[i].meals = 0;
		cfg->philos[i].last_meal = cfg->first_timestamp;
		cfg->philos[i].is_finished = FALSE;
		cfg->philos[i].left_fork = &cfg->forks[i];
		cfg->philos[i].right_fork = &cfg->forks[(i + 1) % cfg->n_philos];
		cfg->philos[i].cfg = cfg;
		pthread_mutex_init(&cfg->philos[i].last_meal_mutex, NULL);
		i++;
	}
	return (TRUE);
}
