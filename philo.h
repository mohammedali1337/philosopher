/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:55:34 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/21 04:36:13 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

typedef struct s_philo
{
    int				id;
    pthread_t		thread;
    long long		last_meal_time; // الوقت لي كلا فيه آخر مرة
    int				meals_eaten;    // عدد المرات لي كلا
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
    struct s_table	*table;         // إشارة للطاولة باش الفيلسوف يقدر يوصل للمعلومات العامة
}   t_philo;

typedef struct s_table
{
    int				num_philos;     // عدد الفلاسفة
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				must_eat_count; // عدد المرات لي خاص الفيلسوف ياكلها

    long long		start_time;     // وقت بداية المحاكاة
    int				is_dead;        // متغير كيحدد واش شي فيلسوف مات

    pthread_mutex_t	*forks;         // مصفوفة ديال Mutexes (كل وحدة تمثل شوكة)
    pthread_mutex_t	write_mutex;    // Mutex باش نمنع الكتابة المتزامنة
    pthread_mutex_t	death_mutex;    // Mutex باش نتحكم في حالة الموت

    t_philo			*philos;        // مصفوفة ديال الفلاسفة
}   t_table;

// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]


int valide_input(char **v, t_table *table);
int	check_if_dead(t_philo *philos);
int	check_if_all_ate(t_philo *philos);
int    init_philo(t_table *table);
int	init_fork(t_table *table);
int start_simulation(t_table *table);
void    sleeping(t_philo *philo);
void    thinking(t_philo *philo);
long	get_time();
void stop_simulation(t_table *table);
void    eat(t_philo *philo);
# endif