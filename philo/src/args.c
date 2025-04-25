/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:15:16 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/25 15:52:11 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	safe_atoi(const char *str, int *values)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	if (result == 0)
		return (0);
	*values = (int)result;
	return (1);
}

int	is_str_digit(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	convert_args(char **argv, int argc, int *values)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_str_digit(argv[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		if (!safe_atoi(argv[i + 1], &values[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_config *config)
{
	int	values[5];

	if (argc < 5 || argc > 6)
		return (0);
	if (!convert_args(argv, argc, values))
		return (0);
	config->n_philos = values[0];
	config->time_die = values[1];
	config->time_eat = values[2];
	config->time_sleep = values[3];
	config->must_eat = -1;
	if (argc == 6)
		config->must_eat = values[4];
	return (1);
}
