/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:14:50 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/25 01:27:10 by mgarouj          ###   ########.fr       */
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
    table->forks = malloc(sizeof(t_forks) * table->nbr_philo);
    if (!table->forks)
        return (free(table->philo), -1);
    return (0);
}

int init_forks(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        if (!(pthread_mutex_init(&table->forks[i].forks_mutex, NULL) == 0))
        {
            write(2, "pthread mutex init error \n", 27);
            return (-1);
        }
        table->forks[i].id_fork = i;
        i++;
    }
    return (0);
}

void assign_forks(t_philo *philo, t_forks *fork, int pos)
{
    int philo_nbr;

    philo_nbr = philo->table->nbr_philo;
    
    philo->r_forks = &fork[(pos + 1) % philo_nbr];
    philo->l_forks = &fork[pos];
    if (philo->id_philo % 2)
    {
        philo->r_forks = &fork[pos];
        philo->l_forks = &fork[(pos + 1) % philo_nbr];
    }
}

int    init_philo(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        table->philo[i].id_philo = i + 1;
        table->philo[i].full = false;
        table->philo[i].meals_counter = 0;
        table->philo[i].table = table;
        assign_forks(&table->philo[i], table->forks, i);
        i++;
    }
    return (0);
}

int    init_data(char **v, t_table *table)
{
    if (init_table(v, table) != 0)
        return (1);
    if (init_forks(table))
        return (1);
    if (init_philo(table))
        return (1);
    return (0);
}