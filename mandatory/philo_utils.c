/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:51:37 by mgarouj           #+#    #+#             */
/*   Updated: 2025/03/13 03:19:14 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void monitoring(t_table *table)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_lock(&table->death_mutex);
			if (get_time() - table->philos[i].last_meal_time >= table->time_to_die)
			{
				printf("Philosopher %d died 💀\n", table->philos[i].id);
				pthread_mutex_unlock(&table->death_mutex);
				return;
			}
			pthread_mutex_unlock(&table->death_mutex);
			i++;
		}
		usleep(1000); // نرتاح قليلاً قبل الفحص الموالي
	}
}

int    init_philo(t_table *table)
{
	int i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return(0);
	i = 0;
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

int	init_fork(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->write_mutex, NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	return (1);
}

void    *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		eat(philo);
		sleeping(philo);
		thinking(philo);
	}
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
	i = 0;
	monitoring(table);
	while (i < table->num_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	stop_simulation(table);
	return (1);
}

