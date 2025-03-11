/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 00:39:38 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/11 19:47:10 by mgarouj          ###   ########.fr       */
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

int valide_input(char **v, t_philo *philo)
{
    if (!ft_isdigit(v))
        return (0);
    
    return 1;
}