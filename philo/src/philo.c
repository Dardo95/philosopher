/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/12 17:03:41 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int	main(int argc, char **argv)
// {
// 	t_config cfg;

// 	if (!parse_args(argc, argv, &cfg)
// 		return (error("Invalid Arguments");
// }

#include "../include/philo.h"
#include <stdio.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (!parse_args(argc, argv, &cfg))
		return (printf("❌ Argumentos inválidos\n"), 1);
	if (!init_config(&cfg))
		return (printf("❌ Error al inicializar cfg\n"), 1);
	if (!init_philosophers(&cfg))
		return (printf("❌ Error al inicializar filósofos\n"), 1);
	pthread_t checker;
	pthread_create(&checker, NULL, death_checker, &cfg);
	if (!start_simulation(&cfg))
		return (printf("❌ Error al lanzar hilos\n"), 1);
	if (!wait_for_threads(&cfg))
		return (printf("❌ Error al esperar hilos\n"), 1);
	pthread_join(checker, NULL);
	return (0);
}
