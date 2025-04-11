/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:15:16 by enogueir          #+#    #+#             */
/*   Updated: 2025/04/11 17:23:00 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int safe_atoi(const char *str, int *out)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
}

int     is_str_digit(char *s)
{
        int     i;

        i = 0;
        if (s[0] == '\0')
                return (0);
        while (s[i] != '\0')
        {
                if (s[i] <= '0' || s[i] >= 9)
                        return (0);
                i++;
        }
        return (1);
}

int     parse_args(argc, argv, &config)
{
        if (argc < 5 || argc > 6)
                return (0);

}
