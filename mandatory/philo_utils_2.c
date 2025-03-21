/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:24:46 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/21 02:55:44 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void stop_simulation(t_table *table)
{
	int i = 0;

	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->death_mutex);
	while (i < table->num_philos)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->forks);
	free(table->philos);
}


long	get_time()
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("philosopher %d had taken a fork \n", philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("philosopher %d had taken a fork \n", philo->id);
	printf("philosopher %d is eating \n", philo->id);
	philo->last_meal_time = get_time();
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void    sleeping(t_philo *philo)
{
    printf("philosopher %d is sleeping \n", philo->id);
    usleep(philo->table->time_to_sleep * 1000);
}

void    thinking(t_philo *philo)
{
    printf("philosopher %d is thinking \n", philo->id);
}