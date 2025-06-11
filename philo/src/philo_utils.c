/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:24:30 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/27 17:25:17 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

unsigned long	get_now_ms(void)
{
	struct timeval	tv;
	unsigned long	current_time;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	current_time = ((tv.tv_sec * 1000 + (tv.tv_usec / 1000)));
	return (current_time);
}

unsigned long	get_timestamp_ms(t_config *cfg)
{
	unsigned long	timestamp;

	timestamp = get_now_ms() - cfg->first_timestamp;
	return (timestamp);
}

void	print_status(t_philo *philo, const char *msg)
{
	t_config	*cfg;

	cfg = philo->cfg;

	if (!run_simulation(cfg))
		return ;
	pthread_mutex_lock(&cfg->write_lock);
	printf("%lu %d %s\n",
		get_timestamp_ms(cfg), philo->id, msg);
	pthread_mutex_unlock(&cfg->write_lock);
}
