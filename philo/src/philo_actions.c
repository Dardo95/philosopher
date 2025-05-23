/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:01 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/23 18:03:48 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
/* 	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_timestamp_ms(philo->cfg);
	pthread_mutex_unlock(&philo->last_meal_mutex); */
}

void	philo_eat(t_philo *philo)
{
	if (simulation_stopped(philo->cfg))
		return ;
	take_forks(philo);
	if (simulation_stopped(philo->cfg))
	{
		release_forks(philo);
		return ;
	}
	print_status(philo, "is eating");
	philo->meals++;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_timestamp_ms(philo->cfg);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	check_full(philo);
	safe_usleep(philo->cfg->time_eat);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	if (simulation_stopped(philo->cfg))
		return ;
	print_status(philo, "is sleeping");
	safe_usleep(philo->cfg->time_sleep);
}

void	philo_think(t_philo *philo)
{
	if (simulation_stopped(philo->cfg))
		return ;
	print_status(philo, "is thinking");
}
