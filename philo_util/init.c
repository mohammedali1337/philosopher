#include "../philo.h"

int init_philo(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_of_philo)
    {
        table->philo[i].id_philo = i + 1;
        table->philo[i].last_meals_time = table->start_time;
        if (pthread_mutex_init(&table->philo[i].l_fork, NULL) != 0)
            return (write(2, "pthread mutex init failed\n", 27), 0);
        if (i + 1 == table->num_of_philo)
            table->philo[i].r_fork = &table->philo[0].l_fork;
        else
            table->philo[i].r_fork = &table->philo[i + 1].l_fork;
        table->philo[i].table = table;
        i++;
    }
    return (1);
}
int stop_loop(t_table *table, int *i)
{
    pthread_mutex_lock(&table->table_mutex);
    if (ft_time_ms() - table->philo[*i].last_meals_time >= (size_t)table->time_to_die || table->philo_fin_eat == table->num_of_philo)
    {
        if (table->limit_meals != -1 && table->philo_fin_eat == table->num_of_philo)
        {
            table->evry_philo_eat = 1;
            pthread_mutex_unlock(&table->philo[*i].l_fork);
            printf("every philosopher has eaten %d times\n", table->limit_meals);
        }
        else
        {
            table->philo_die = 1;
            pthread_mutex_unlock(&table->philo[*i].l_fork);
            printf("%lu %d died\n", ft_time_ms() - table->start_time, table->philo[*i].id_philo);
        }
        pthread_mutex_unlock(&table->table_mutex);
        return (1);
    }
    if (*i + 1 == table->num_of_philo)
        *i = 0;
    pthread_mutex_unlock(&table->table_mutex);
    return (0);
}

int thread_creat(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_of_philo)
    {
        if (pthread_create(&table->philo[i].thread, NULL, routine, &table->philo[i]))
            return(write(2, "pthread creat error\n", 21), 0);
        i++;
    }
    i = 0;
    while (i < table->num_of_philo && !stop_loop(table, &i))
        i++;
    i = 0;
    while (i < table->num_of_philo)
        pthread_join(table->philo[i++].thread, NULL);
    i = 0;
    while (i < table->num_of_philo)
        pthread_mutex_destroy(&table->philo[i++].l_fork);
    return (1);
}