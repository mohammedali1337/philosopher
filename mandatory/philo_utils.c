/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:51:37 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/12 02:21:03 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int    init_table(t_table *table)
{
	int i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return(0);
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal_time = 0;
		table->philos[i].meals_eaten = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[i + 1];
		table->philos[i].table = table;
		i++;
	}
	return (1);
}

void    *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	printf("philosopher %d is thinking... \n", philo->id);
	return (NULL);
}

int start_simulation(t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
			return (printf("failed creat thread \n"), 0);
		i++;
	}
	return (1);
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
	unsleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}