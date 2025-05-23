/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:24:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/23 17:51:36 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_timestamp_ms(t_config *cfg)
{
	return (get_now_ms() - cfg->first_timestamp);
}

void	safe_usleep(long time_ms)
{
	long	start;

	start = get_now_ms();
	while ((get_now_ms() - start) < time_ms)
		usleep(3);
}

void	print_status(t_philo *philo, const char *msg)
{
	t_config	*cfg;

	cfg = philo->cfg;
	pthread_mutex_lock(&cfg->write_lock);
	if (!simulation_stopped(cfg))
		printf("%ld %d %s\n",
			get_timestamp_ms(cfg), philo->id, msg);
	pthread_mutex_unlock(&cfg->write_lock);
}
