/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:39:38 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/11 21:37:46 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(char **v)
{
    int i;
    int j;

    i = 1;
    while (v[i])
    {
        j = 0;
        while (v[i][j])
            if (!(v[i][j] >= '0' && v[i][j++] <= '9'))
                return (0);
        i++;
    }
    return (1);
}

static int	sign_spc(char *str, int *skip)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*skip = i;
	return (sign);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	o;

	i = 0;
	result = 0;
	sign = sign_spc((char *)str, &i);
	while (((char *)str)[i] >= '0' && ((char *)str)[i] <= '9')
	{
	o = result;
		result = result * 10 + (((char *)str)[i++] - 48);
		if ((result / 10) != o)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
	}
	return (result * sign);
}

int valide_number_of_philo(char **v, t_table *table)
{
    table->num_philos = ft_atoi(v[1]);
	table->time_to_die = ft_atoi(v[2]);
	table->time_to_eat = ft_atoi(v[3]);
	table->time_to_sleep = ft_atoi(v[4]);
	table->start_time = (v[5] != NULL) ? ft_atoi(v[5]) : -1;
    if (table->num_philos <= 0)
        return (0);
    return (1);
}

int valide_input(char **v, t_table *table)
{
    if (!ft_isdigit(v))
        return (0);
    if (!valide_number_of_philo(v, table))
        return (0);
    return 1;
}