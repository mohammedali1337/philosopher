#include "philo.h"

int philo_dead(t_philo *philo, t_table *table)
{
    pthread_mutex_lock(philo->meal_lock);
    if (get_time() - philo->last_meal_time >= table->death_time
        && !philo->is_eating)
        return (pthread_mutex_unlock(philo->meal_lock), 1);
    pthread_mutex_unlock(philo->meal_lock);
    return (0);
}

void    ft_print(char *str, t_philo *philo)
{
    size_t  time;

    pthread_mutex_lock(philo->output_lock);
    time = get_time() - philo->simulation_start;
    if (!dead(philo))
        printf("%zu %d %s\n", time, philo->philo_id, str);
    pthread_mutex_unlock(philo->output_lock);
}

int check_philo_dead(t_table *table)
{
    int i;

    i = 0;
    while (i < table->total_philos)
    {
        if (philo_dead(&table->philo[i], table))
        {
            ft_print("died", &table->philo[i]);
            pthread_mutex_lock(table->philo[0].death_lock);
            *table->philo->is_dead = 1;
            pthread_mutex_unlock(table->philo[0].death_lock);
            return (1);
        }
        i++;
    }
    return (0);
}

int check_philo_eat(t_table *table)
{
    int i;
    int fin_eat;

    i = 0;
    fin_eat = 0;
    if (table->eat_duration == -1)
        return (0);
    while (i < table->total_philos)
    {
        pthread_mutex_lock(table->philo[i].meal_lock);
        if (table->philo[i].meals_count >= table->eat_duration)
            fin_eat++;
        pthread_mutex_unlock(table->philo[i].meal_lock);
        i++;
    }
    if (fin_eat == table->total_philos)
    {
        pthread_mutex_lock(table->philo[0].death_lock);
        *table->philo->is_dead = 1;
        pthread_mutex_unlock(table->philo[0].death_lock);
        return (1);
    }
    return (0);
}

void    *monitor(void *arg)
{
    t_table *table;

    table = (t_table *)arg;
    while (1)
        if (check_philo_dead(table) || check_philo_eat(table))
            break;
    return (arg);
}