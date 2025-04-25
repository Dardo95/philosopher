/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:38:32 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/25 15:43:13 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_config
{
	int	n_philos;
	int time_die;
	int time_eat;
	int time_sleep;
	int must_eat;
}	t_config;


int	is_str_digit(char *s);
int	safe_atoi(const char *str, int *values);
int	convert_args(char **argv, int argc, int *values);
int	parse_args(int argc, char **argv, t_config *config);


#endif
