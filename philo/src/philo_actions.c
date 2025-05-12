/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:13:01 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/12 21:46:33 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_full(t_philo *philo)
{
	if (philo->cfg->must_eat > 0 && philo->meals == philo->cfg->must_eat)
	{
		pthread_mutex_lock(&philo->cfg->full_mutex);
		philo->cfg->philos_full++;
		pthread_mutex_unlock(&philo->cfg->full_mutex);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(philo->cfg),
		philo->id);
	pthread_mutex_unlock(&philo->cfg->write_lock);
	if (simulation_stopped(philo->cfg))
		return (pthread_mutex_unlock(first_fork), (void)0);
	pthread_mutex_lock(second_fork);
	pthread_mutex_lock(&philo->cfg->write_lock);
	printf("%ld %d has taken a fork\n", get_timestamp_ms(philo->cfg),
		philo->id);
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
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
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
