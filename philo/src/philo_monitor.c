/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:34 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/23 17:52:53 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_philo_death(t_philo *philo)
{
	time_t	now;

	pthread_mutex_lock(&philo->last_meal_mutex);
	now = get_timestamp_ms(philo->cfg);
	if (now - philo->last_meal >= philo->cfg->time_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_lock(&philo->cfg->write_lock);
		printf("%ld %d died\n", now, philo->id);
		pthread_mutex_unlock(&philo->cfg->write_lock);
		pthread_mutex_lock(&philo->cfg->stop_mutex);
		philo->cfg->stop = 1;
		pthread_mutex_unlock(&philo->cfg->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	*death_checker(void *arg)
{
	t_config	*cfg;
	int			i;

	cfg = (t_config *)arg;
	while (!simulation_stopped(cfg))
	{
		i = 0;
		while (i < cfg->n_philos)
		{
			if (check_philo_death(&cfg->philos[i]))
				return (NULL);
			i++;
		}
		safe_usleep(1);
	}
	return (NULL);
}

void	check_full(t_philo *philo)
{
	if (philo->cfg->must_eat > 0 && philo->meals == philo->cfg->must_eat)
	{
		pthread_mutex_lock(&philo->cfg->full_mutex);
		philo->cfg->philos_full++;
		pthread_mutex_unlock(&philo->cfg->full_mutex);
	}
}

void	*meals_complete(void *arg)
{
	t_config	*cfg;

	cfg = (t_config *)arg;
	while (!simulation_stopped(cfg))
	{
		pthread_mutex_lock(&cfg->full_mutex);
		if (cfg->must_eat > 0 && cfg->philos_full == cfg->n_philos)
		{
			pthread_mutex_unlock(&cfg->full_mutex);
			pthread_mutex_lock(&cfg->stop_mutex);
			cfg->stop = 1;
			pthread_mutex_unlock(&cfg->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&cfg->full_mutex);
		usleep(1000);
	}
	return (NULL);
}
