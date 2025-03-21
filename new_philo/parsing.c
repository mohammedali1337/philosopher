/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 05:37:02 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/21 06:36:34 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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