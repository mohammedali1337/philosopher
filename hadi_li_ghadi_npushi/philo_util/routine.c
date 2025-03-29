#include "../philo.h"

int stop_simulation(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->table_mutex);
    if (philo->table->philo_die || philo->table->evry_philo_eat)
        return (pthread_mutex_unlock(&philo->table->table_mutex), 1);
    return (pthread_mutex_unlock(&philo->table->table_mutex), 0);
}

int print_status(char *str, t_philo *philo)
{
    pthread_mutex_lock(&philo->table->table_mutex);
    if (philo->table->philo_die || philo->table->evry_philo_eat)
        return (pthread_mutex_unlock(&philo->table->table_mutex), 0);
    printf("%lu %d %s\n", ft_time_ms() - philo->table->start_time, philo->id_philo, str);
    pthread_mutex_unlock(&philo->table->table_mutex);
    return (1);
}

int get_fork(t_philo *philo)
{
    if (stop_simulation(philo))
        return (0);
    pthread_mutex_lock(&philo->l_fork);
    if (!print_status("has taking a fork", philo))
        return(pthread_mutex_unlock(&philo->l_fork), 0);
    if (stop_simulation(philo))
        return (0);
    pthread_mutex_lock(philo->r_fork);
    if (!print_status("has taking a fork", philo))
        return(pthread_mutex_unlock(&philo->l_fork), pthread_mutex_unlock(philo->r_fork), 0);
    return (1);
}

int thinking_sleeping(t_philo *philo)
{
    if (!print_status("is sleeping", philo))
        return (0);
    ft_usleep(philo->table->time_to_sleep);
    if (!print_status("is eating", philo))
        return (0);
    return (1);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (!(philo->id_philo % 2))
        ft_usleep(10);
    while (1)
    {
        if (!get_fork(philo))
            break;
        pthread_mutex_lock(&philo->table->table_mutex);
        philo->meal_count++;
        philo->last_meals_time = ft_time_ms();
        pthread_mutex_unlock(&philo->table->table_mutex);
        print_status("is eating", philo);
        ft_usleep(philo->table->time_to_eat);
        pthread_mutex_lock(&philo->table->table_mutex);
        if (philo->meal_count == philo->table->limit_meals)
            philo->table->philo_fin_eat += (philo->table->limit_meals != -1);
        pthread_mutex_unlock(&philo->table->table_mutex);
        pthread_mutex_unlock(&philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        if (!thinking_sleeping(philo))
            break;
    }
    return (NULL);
}