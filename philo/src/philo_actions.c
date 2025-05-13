/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:01 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/13 18:41:34 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	release_forks(t_philo *philo)
{
	
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->first = philo->right_fork;
		philo->second = philo->left_fork;
	}
	else
	{
		philo->first = philo->left_fork;
		philo->second = philo->right_fork;
	}
	pthread_mutex_lock(philo->first);
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(philo->cfg), philo->id);
	pthread_mutex_unlock(&philo->cfg->write_lock);

	if (simulation_stopped(philo->cfg))
		return ((void)pthread_mutex_unlock(philo->first));

	pthread_mutex_lock(philo->second);
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(philo->cfg), philo->id);
	pthread_mutex_unlock(&philo->cfg->write_lock);
}


void	philo_eat(t_philo *philo)
{
	if (simulation_stopped(philo->cfg))
		return ;
	take_forks(philo);
	if (simulation_stopped(philo->cfg))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d is eating\n", get_timestamp_ms(philo->cfg), philo->id);
	pthread_mutex_unlock(&philo->cfg->write_lock);
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_timestamp_ms(philo->cfg);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	philo->meals++;
	check_full(philo);
	usleep(philo->cfg->time_eat * 1000);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (simulation_stopped(philo->cfg))
		return ;
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d is sleeping\n", get_timestamp_ms(philo->cfg), philo->id);
	pthread_mutex_unlock(&philo->cfg->write_lock);
	usleep(philo->cfg->time_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	if (simulation_stopped(philo->cfg))
		return ;
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d is thinking\n", get_timestamp_ms(philo->cfg), philo->id);
	pthread_mutex_unlock(&philo->cfg->write_lock);
}
