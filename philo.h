/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:55:34 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/11 01:07:56 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

typedef struct s_philo
{
    int             id;             // Philosopher ID (from 0 to N-1)
    int             meals_eaten;     // Number of times the philosopher has eaten
    long long       last_meal_time;  // Timestamp of the last meal
    pthread_t       thread_id;       // Thread ID for the philosopher
    pthread_mutex_t *left_fork;      // Pointer to the left fork mutex
    pthread_mutex_t *right_fork;     // Pointer to the right fork mutex
}   t_philo;


// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]


int valide_input(char **v, t_philo *philo);
# endif