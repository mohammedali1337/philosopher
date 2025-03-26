#include "../philo.h"

size_t    ft_time_ms(void)
{
	struct timeval  tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL);
}

int check_args(char *str, char *max_i)
{
    int i;
    int len;

    i = 0;
    if (str[i] == '+')
        i++;
    // while (str[i] == '0')
    //     i++;
    len = ft_strlen(str + i);
    if (len <= 10)
    {
        if (len == 10)
            while (ft_isdigit(str[i]) && str[i] <= *max_i++)
                i++;
        else
            while (ft_isdigit(str[i]))
                i++;
    }
    else
        return (0);
    if (!str[i])
        return (1);
    else
        return (0);
}

int init_table(t_table *table, char **v)
{
    int i;

    i = 1;
    while (v[i])
        if (!check_args(v[i++], "2147483647"))
            return (0);
    table->num_of_philo = ft_atoi(v[1]);
    table->time_to_die = ft_atoi (v[2]);
    table->time_to_eat = ft_atoi(v[3]);
    table->time_to_sleep = ft_atoi(v[4]);
    if (table->num_of_philo > 200)
        return (write(2, "num of philo error\n", 20), 0);
    if (v[5])
        table->limit_meals = ft_atoi(v[5]);
    else 
        table->limit_meals = -1;
    if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
        return (write(2, "error pthread mutex\n", 21), 0);
    table->philo = malloc(sizeof(t_philo) * table->num_of_philo);
    if (!table->philo)
        return (write(2, "failed allocat philo\n", 22), 0);
    table->start_time = ft_time_ms();
    return (1);
}
