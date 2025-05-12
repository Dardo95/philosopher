/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:24:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/12 17:03:41 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_now_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	
}

long	get_timestamp_ms(t_config *cfg)
{
	return (get_now_ms() - cfg->first_timestamp);
}

int	simulation_stopped(t_config *cfg)
{
	int	stopped;

	pthread_mutex_lock(&cfg->stop_mutex);
	stopped = cfg->stop;
	pthread_mutex_unlock(&cfg->stop_mutex);
	return (stopped);
}
