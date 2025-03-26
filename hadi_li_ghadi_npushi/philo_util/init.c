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
    }
    return (1);
}

int thread_creat(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_of_philo)
        if (pthread_create(&table->philo[i].thread, NULL, routine, &table->philo[i++]))
            return(write(2, "pthread creat error\n", 21), 0);
}