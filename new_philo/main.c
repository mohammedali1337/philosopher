/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 04:46:42 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/21 23:31:26 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int valide_input(int c, char **v, int i)
{
    
    if (c != 6 && c !=6)
    {
        write(2, "Usage: ./philo number_of_philos time_to_die time_to_eat time_to_sleep [must_eat]\n", 82);
        return (1);
    }
    if (!ft_isdigit(v))
        return (write(2, "invalide argument\n", 19), -1);
    while (v[i])
    {
        if (i == 1 && ft_atoi(v[i]) > 300 || ft_atoi(v[i]) <= 0)
            return (write(2, "Invalid philosophers number\n", 29), -1);
        if (i == 2 && ft_atoi(v[i]) <= 0)
            return (write(2, "Invalide time to die\n", 22), -1);
        if (i == 3 && ft_atoi(v[i]) <= 0)
            return (write(2, "Invalide time to eat\n", 22), -1);
        if (i == 4 && ft_atoi(v[i]) <= 0)
            return (write(2, "Invalide time to sleep\n", 24), -1);
        if (i == 5 && ft_atoi(v[i]) < 0 )
            return (write(2, "invalide number of times each philosopher must eat\n", 52), -1);
        i++;
    }
    return (0);
}

int init_table(t_table *table, char **v, int i)
{
    table->total_philos = ft_atoi(v[1]);
    table->death_time = ft_atoi(v[2]);
    table->eat_duration = ft_atoi(v[3]);
    table->sleep_duration = ft_atoi(v[4]);
    if (v[5])
        table->required_meals = ft_atoi(v[5]);
    else
        table->required_meals = -1;
    table->death_status = 0;
    table->philo = malloc(sizeof(t_philo) * table->total_philos);
    table->forks = malloc(sizeof(pthread_mutex_t) * table->total_philos);
    if (!table->philo || !table->forks)
        return (-1);
    pthread_mutex_init(&table->death_lock, NULL);
    pthread_mutex_init(&table->output_lock, NULL);
    pthread_mutex_init(&table->meal_lock, NULL);
    while (i < table->total_philos)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    return (0);
}

void    init_philo(t_table *table, char **v)
{
   int  i;

   i = 0;
   while (i < table->total_philos)
   {
        table->philo[i].philo_id = i + 1;
        table->philo[i].is_eating = 0;
        table->philo[i].meals_count = 0;
        table->philo[i].simulation_start = get_time();
        table->philo[i].last_meal_time = get_time();
        table->philo[i].output_lock = &table->output_lock;
        table->philo[i].death_lock = &table->death_lock;
        table->philo[i].meal_lock = &table->meal_lock;
        table->philo[i].is_dead = &table->death_status;
        table->philo[i].left_fork = &table->forks[i];
        if (i == 0)
            table->philo[i].right_fork = &table->forks[table->total_philos - 1];
        else
            table->philo->right_fork = &table->forks[i - 1];
        table->philo[i].table = table;
        i++;
   }
}

int main(int c, char **v)
{
    t_table table;
    if (!(valide_input(c, v, 1) == 0))
        return (1);
    if (!(init_table(&table, v, 0) == 0))
        return (2);
    init_philo(&table, v);
    // printf("note this \n");
    create_thread_philo(&table);
    des_free_all(NULL, &table);
    return (0);
}