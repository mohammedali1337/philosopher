/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:14:50 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/24 23:29:37 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_table(char **v, t_table *table)
{
    table->end_simulation = false;
    table->nbr_philo= ft_atoi(v[1]);
    table->time_to_die = ft_atoi(v[2]);
    table->time_to_eat = ft_atoi(v[3]);
    table->time_to_sleep = ft_atoi(v[4]);
    if (v[5])
        table->nbr_limit_meals= ft_atoi(v[5]);
    else
        table->nbr_limit_meals = -1;
    table->philo = malloc(sizeof(t_philo) * table->nbr_philo);
    if (!table->philo)
        return (-1);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philo);
    
}

void    init_data(char **v, t_table *table)
{
    init_table(v, table);
}