#include "philo.h"

void des_free_all(char *str, t_table *table)
{
    int i;

    i = 0;
    if (str)
        write(2, str, ft_strlen(str));
    pthread_mutex_destroy(&table->output_lock);
    pthread_mutex_destroy(&table->meal_lock);
    pthread_mutex_destroy(&table->death_lock);
    while (i < table->total_philos)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    free(table->forks);
    free(table->philo);
}