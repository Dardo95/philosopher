/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:34 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/27 17:27:15 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	stop_simulation_run(t_config *cfg)
{
	pthread_mutex_lock(&cfg->run_mutex);
	cfg->running = FALSE;
	pthread_mutex_unlock(&cfg->run_mutex);
}

int	check_death(t_config *cfg, t_philo *philo)
{
	if (get_now_ms() - philo->last_meal > cfg->time_die)
	{
		pthread_mutex_lock(&cfg->write_lock);
		printf("%lu %d %s\n",
		get_timestamp_ms(cfg), philo->id, "is dead");
		stop_simulation_run(cfg);
		pthread_mutex_unlock(&cfg->write_lock);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (TRUE);
	}
	return (FALSE);
}

int philo_full_eat(t_config *cfg, t_philo *philo, int *philos_full)
{
    if (philo->is_finished == FALSE)
    {
        if (cfg->must_eat != -1 && philo->meals >= cfg->must_eat)
        {
            philo->is_finished = TRUE;
            print_status(philo, "has finished eating");
            (*philos_full)++;
            return (TRUE);
        }
        return (FALSE);
    }
    else
    {
        (*philos_full)++;
        return (TRUE);
    }
}


void *checker_routine(void *arg)
{
	t_config	*cfg;
    int			i;
    int			philos_full;

	cfg = (t_config *)arg;
	while (TRUE)
	{
		usleep(500);
		philos_full = 0;
		i = 0;
		while (i < (int)cfg->n_philos)
		{
			if (!run_simulation(cfg))
				return (NULL);
			pthread_mutex_lock(&cfg->philos[i].last_meal_mutex);
			if (check_death(cfg, &cfg->philos[i]))
				return (NULL);
			philo_full_eat(cfg, &cfg->philos[i], &philos_full);
			pthread_mutex_unlock(&cfg->philos[i].last_meal_mutex);
			i++;
		}
		if (cfg->must_eat > 0 && philos_full == (int)cfg->n_philos)
			return (stop_simulation_run(cfg), NULL);
	}
	return (NULL);
}

