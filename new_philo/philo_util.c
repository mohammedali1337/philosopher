#include "philo.h"

size_t get_time()
{
    struct timeval  time;

    if (gettimeofday(&time, NULL) == -1)
        write(2, "error in gettimeofday()\n", 25);
    return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

int create_thread_philo(t_table *table)
{
    pthread_t   observer;
    int         i;

    if (pthread_create(&observer, NULL, &monitor, table))
        des_free_all("thead creation error\n", table);
    i = 0;
    while (i < table->total_philos)
    {
        // if (pthread_create(&table->philo[i], NULL, &philosopher)
    }
    
}