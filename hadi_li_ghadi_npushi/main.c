#include "philo.h"

int main(int c, char **v)
{
    t_table table;

    if (c != 5 && c != 6)
        return (1);
    if (!init_table(&table, v))
        return (2);
    if (!init_philo(&table))
        return (3);
    if (!thread_creat(&table))
        return (4);
    // printf("not this \n");
    return (0);
}