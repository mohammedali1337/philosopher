/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:59:40 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/26 01:31:18 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void    wait_all_threads(t_table *table)
{
    return ;
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;

    wait_all_threads(philo->table);
    
    return (NULL);
}

int    creat_thread_philo(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        if (pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]) != 0)
            return (-1);
        i++;
    }

    
    return (0);
}