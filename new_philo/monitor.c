#include "philo.h"

int philo_dead(t_philo *philo, t_table *table)
{
    pthread_mutex_lock(philo->meal_lock);
    if (get_time - philo->last_meal_time >= table->death_time
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
    if (!)
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
        }
    }
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