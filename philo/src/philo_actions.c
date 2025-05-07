/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:01 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/07 15:13:25 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(philo->config),
		philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(philo->config),
		philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d is eating\n", get_timestamp_ms(philo->config), philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);
	philo->last_meal = get_timestamp_ms(philo->config);
	philo->meals++;
	usleep(philo->config->time_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d is sleeping\n", get_timestamp_ms(philo->config), philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);
	usleep(philo->config->time_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->write_lock);
	printf("%ld %d is thinking\n", get_timestamp_ms(philo->config), philo->id);
	pthread_mutex_unlock(&philo->config->write_lock);
}