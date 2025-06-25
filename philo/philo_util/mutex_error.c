#include "../philo.h"

void    ft_destroy_mutex(t_table *table, int flag, int i, int print)
{
    if (flag == 't')
    {
        free(table->philo);
        pthread_mutex_destroy(&table->table_mutex);
        if (print)
            write(2, "argument not valide \n", 22);
    }
    else if (flag == 'f')
    {
        if (print)
            write(2, "pthread mutex init failed\n", 27);
        while (--i >= 0)
            pthread_mutex_destroy(&table->philo[i].l_fork);
        ft_destroy_mutex(table, 't', 0, 0);
    }
}

void    ft_destroy_thread(t_table *table)
{
    write(2, "pthread create error\n", 22);
    ft_destroy_mutex(table, 'f', table->num_of_philo, 0);
}