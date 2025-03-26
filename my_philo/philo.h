/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:31:07 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/26 01:43:50 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

// struct of forks

typedef struct s_forks
{
    pthread_mutex_t forks_mutex;
    int id_fork;
}   t_forks;

// struct of philo  ./philo 5 800 200 200 [5]

typedef struct s_philo
{
    pthread_t thread;
    int id_philo;
    long meals_counter;
    bool full;
    long    las_meal_time;
    t_forks *r_forks;
    t_forks *l_forks;
    struct s_table *table;
}   t_philo;


// struct of table 

typedef struct s_table
{
    int nbr_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long nbr_limit_meals;
    long start_simulation;
    bool end_simulation;
    bool all_threads_ready;
    pthread_mutex_t table_mutex;
    t_forks *forks;
    t_philo *philo;
}   t_table;


// int valide_input(char **v, t_table *table);
int    creat_thread_philo(t_table *table);
int    init_data(char **v, t_table *table);
int	ft_atoi(const char *str);