/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/06 12:55:47 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int	main(int argc, char **argv)
// {
// 	t_config config;

// 	if (!parse_args(argc, argv, &config)
// 		return (error("Invalid Arguments");
// }

#include "../include/philo.h"
#include <stdio.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	config;

	if (!parse_args(argc, argv, &config))
		return (printf("❌ Argumentos inválidos\n"), 1);
	if (!init_config(&config))
		return (printf("❌ Error al inicializar config\n"), 1);
	if (!init_philosophers(&config))
		return (printf("❌ Error al inicializar filósofos\n"), 1);
	if (!start_simulation(&config))
		return (printf("❌ Error al lanzar hilos\n"), 1);
	if (!wait_for_threads(&config))
		return (printf("❌ Error al esperar hilos\n"), 1);
	return (0);
}
