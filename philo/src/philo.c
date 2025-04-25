/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/25 17:51:44 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int	main(int argc, char **argv)
// {
// 	t_config config;

// 	if (!parse_args(argc, argv, &config)
// 		return (error("Invalid Arguments");
// }

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	config;

	if (!parse_args(argc, argv, &config))
	{
		printf("❌ Error: argumentos inválidos\n");
		return (1);
	}
	printf("✅ Argumentos parseados correctamente:\n");
	printf("Número de filósofos:         %d\n", config.n_philos);
	printf("Tiempo para morir (ms):      %d\n", config.time_die);
	printf("Tiempo para comer (ms):      %d\n", config.time_eat);
	printf("Tiempo para dormir (ms):     %d\n", config.time_sleep);
	printf("Veces que debe comer cada uno: ");
	if (config.must_eat == -1)
		printf("no especificado\n");
	else
		printf("%d\n", config.must_eat);
	return (0);
}