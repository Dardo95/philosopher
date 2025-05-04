/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:14:59 by enogueir          #+#    #+#             */
/*   Updated: 2025/05/04 20:09:48 by enogueir         ###   ########.fr       */
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
	int			i;

	if (!parse_args(argc, argv, &config))
		return (printf("❌ Argumentos inválidos\n"), 1);
	if (!init_config(&config))
		return (printf("❌ Error al inicializar forks y philos\n"), 1);
	if (!init_philosophers(&config))
		return (printf("❌ Error al inicializar filósofos\n"), 1);

	printf("✅ Filósofos inicializados correctamente:\n\n");
	i = 0;
	while (i < config.n_philos)
	{
		t_philo *p = &config.philos[i];
		printf("Filósofo %d:\n", p->id);
		printf("  Meals: %d\n", p->meals);
		printf("  Left fork:  %p\n", (void *)p->left_fork);
		printf("  Right fork: %p\n", (void *)p->right_fork);
		printf("  Config ptr: %p\n", (void *)p->config);
		printf("\n");
		i++;
	}
	return (0);
}
