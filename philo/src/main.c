/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/11 20:31:17 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void free_and_destroy(t_config	*cfg)
{
	int	i;

	i = 0;
	while (i < (int)cfg->n_philos)
	{
		pthread_mutex_destroy(&cfg->forks[i]);
		pthread_mutex_destroy(&cfg->philos[i].last_meal_mutex);
		i++;
	}
	free(cfg->forks);
	free(cfg->philos);
	pthread_mutex_destroy(&cfg->run_mutex);
	pthread_mutex_destroy(&cfg->write_lock);
}

int	main(int argc, char **argv)
{
	t_config	cfg;
	pthread_t checker;

	memset(&cfg, 0, sizeof (t_config));
	if (!parse_args(argc, argv, &cfg))
		return (printf("Failed Arguments\n"), EXIT_FAILURE);
	if (cfg.must_eat == 0)
		return (FALSE);
	if (!init_config(&cfg))
		return (printf("Error al inicializar cfg\n"), EXIT_FAILURE);
	if (!init_philosophers(&cfg))
	{
		printf("Error al inicializar filósofos\n");
		free_and_destroy(&cfg);
		return (EXIT_FAILURE);
	}
	if (!start_simulation(&cfg, &checker))
		return (EXIT_FAILURE);

	wait_for_threads(&cfg, checker);
	free_and_destroy(&cfg);
	return (EXIT_SUCCESS);
}
