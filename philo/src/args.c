/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:15:16 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/25 13:23:56 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	safe_atoi(const char *str, int *values)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (str[0] == '+')
		i = 1;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (FALSE);
		i++;
	}
	*values = (int)result;
	return (TRUE);
}

int	is_str_digit(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '\0')
		return (FALSE);
	if (s[0] == '+')
		i = 1;
	if (s[i] == '\0')
		return (FALSE);
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	convert_args(char **argv, int argc, int *values)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_str_digit(argv[i]))
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		if (!safe_atoi(argv[i + 1], &values[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	parse_args(int argc, char **argv, t_config *cfg)
{
	int	values[5];

	if (argc < 5 || argc > 6)
		return (FALSE);
	if (!convert_args(argv, argc, values))
		return (FALSE);
	if (values[0] <= 0 || values[1] <= 0 || values[2] <= 0
		|| values[3] <= 0)
		return (FALSE);
	cfg->n_philos = values[0];
	cfg->time_die = values[1];
	cfg->time_eat = values[2];
	cfg->time_sleep = values[3];
	cfg->must_eat = -1;
	if (argc == 6)
		cfg->must_eat = values[4];
	return (TRUE);
}
