/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarouj <mgarouj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:16:18 by mgarouj           #+#    #+#             */
/*   Updated: 2025/06/13 13:50:56 by mgarouj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philo)
	{
		table->philo[i].id_philo = i + 1;
		table->philo[i].last_meals_time = table->start_time;
		table->philo[i].meal_count = 0;
		if (pthread_mutex_init(&table->philo[i].l_fork, NULL) != 0)
			return (write(2, "pthread mutex init failed\n", 27), 0);
		if (i + 1 == table->num_of_philo)
			table->philo[i].r_fork = &table->philo[0].l_fork;
		else
			table->philo[i].r_fork = &table->philo[i + 1].l_fork;
		table->philo[i].table = table;
		i++;
	}
	return (1);
}

int	fin_or_dead(t_table *table, int *i)
{
	// printf("philo fin eat = %d \n num of meals = %d \n", table->evry_philo_eat, table->philo[0].meal_count)
	if (ft_time_ms() - table->philo[*i].last_meals_time
		>= (size_t)table->time_to_die
		|| table->philo_fin_eat == table->num_of_philo)
		return (1);
	return (0);
}

int	stop_loop(t_table *table, int *i)
{
	pthread_mutex_lock(&table->table_mutex);
	if (fin_or_dead(table, i))
	{
		if (table->limit_meals != -1
			&& table->philo_fin_eat == table->num_of_philo)
		{
			table->evry_philo_eat = 1;
			pthread_mutex_unlock(&table->philo[*i].l_fork);
			printf("every philosopher has eaten %d times\n",
				table->limit_meals);
		}
		else
		{
			table->philo_die = 1;
			pthread_mutex_unlock(&table->philo[*i].l_fork);
			printf("%lu %d died\n", ft_time_ms() - table->start_time,
				table->philo[*i].id_philo);
		}
		pthread_mutex_unlock(&table->table_mutex);
		return (1);
	}
	if (*i + 1 == table->num_of_philo)
		*i = 0;
	pthread_mutex_unlock(&table->table_mutex);
	return (0);
}

int	thread_creat(t_table *table)
{
	int	i;

	i = 0;
	if (table->num_of_philo == 1)
		return (printf("%lu 1 died\n", ft_time_ms() - table->start_time), 1);
	while (i < table->num_of_philo)
	{
		if (pthread_create(&table->philo[i].thread,
				NULL, routine, &table->philo[i]))
			return (write(2, "pthread creat error\n", 21), 0);
		i++;
	}
	i = 0;
	while (i < table->num_of_philo && !stop_loop(table, &i))
	{
		i++;
	}
	i = 0;
	while (i < table->num_of_philo)
		pthread_join(table->philo[i++].thread, NULL);
	i = 0;
	while (i < table->num_of_philo)
		pthread_mutex_destroy(&table->philo[i++].l_fork);
	return (1);
}
