/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:47:09 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/27 13:52:02 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int start_simulation(t_config *cfg, pthread_t *checker)
{
	int i;

	i = 0;
	while (i < (int)cfg->n_philos)
	{
		pthread_create(&cfg->philos[i].thread, NULL,
			routine, &cfg->philos[i]);
		i++;
	}

	if (pthread_create(checker, NULL, checker_routine, cfg) != 0)
    {
        wait_for_threads(cfg, *checker);
        free_and_destroy(cfg);
        return (FALSE);
    }

    return (TRUE);
}

void wait_for_threads(t_config *cfg, pthread_t checker)
{
	int i;

	pthread_join(checker, NULL);
	i = 0;
	while (i < (int)cfg->n_philos)
	{
		pthread_join(cfg->philos[i].thread, NULL);
		i++;
	}
}