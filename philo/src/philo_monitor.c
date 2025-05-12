/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:34 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/12 21:39:40 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


int	check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (get_timestamp_ms(philo->cfg) - philo->last_meal >= philo->cfg->time_die)
	{
		pthread_mutex_lock(&philo->cfg->write_lock);
		printf("%ld %d died\n", get_timestamp_ms(philo->cfg), philo->id);
		pthread_mutex_unlock(&philo->cfg->write_lock);
		pthread_mutex_lock(&philo->cfg->stop_mutex);
		philo->cfg->stop = 1;
		pthread_mutex_unlock(&philo->cfg->stop_mutex);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	*death_checker(void *arg)
{
	t_config 	*cfg = (t_config *)arg;
	int			i;

	while (!simulation_stopped(cfg))
	{
		i = 0;
		while (i < cfg->n_philos)
		{
			if (check_philo_death(&cfg->philos[i]))
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&cfg->full_mutex);
		if (cfg->must_eat > 0 && cfg->philos_full == cfg->n_philos)
		{
			pthread_mutex_lock(&cfg->stop_mutex);
			cfg->stop = 1;
			pthread_mutex_unlock(&cfg->stop_mutex);
			pthread_mutex_unlock(&cfg->full_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&cfg->full_mutex);
		usleep(1000);
	}
	return (NULL);
}
