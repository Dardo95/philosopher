/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/23 17:17:39 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void free_and_destroy(t_config	cfg)
{
	int	i;

	i = 0;
	while (i < cfg.n_philos)
	{
		pthread_mutex_destroy(&cfg.forks[i]);
		pthread_mutex_destroy(&cfg.philos[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&cfg.stop_mutex);
	pthread_mutex_destroy(&cfg.write_lock);
	pthread_mutex_destroy(&cfg.full_mutex);
	free(cfg.forks);
	free(cfg.philos);
}

int	main(int argc, char **argv)
{
	t_config	cfg;
	pthread_t checker;
	pthread_t meals_thread;

	if (!parse_args(argc, argv, &cfg))
		return (printf("Argumentos inválidos\n"), 1);
	if (!init_config(&cfg))
		return (printf("Error al inicializar cfg\n"), 1);
	if (!init_philosophers(&cfg))
		return (printf("Error al inicializar filósofos\n"), 1);
	if (cfg.must_eat > 0)
		pthread_create(&meals_thread, NULL, meals_complete, &cfg);
	if (pthread_create(&checker, NULL, death_checker, &cfg))
		return (printf("Failed Create\n"), 1);
	if (!start_simulation(&cfg))
		return (printf("Error al lanzar hilos\n"), 1);
	if (!wait_for_threads(&cfg))
		return (printf("Error al esperar hilos\n"), 1);
	if (pthread_join(checker, NULL))
		return (printf("Failed join checker\n"), 1);
	if (cfg.must_eat > 0)
		pthread_join(meals_thread, NULL);
	free_and_destroy(cfg);
	return (0);
}