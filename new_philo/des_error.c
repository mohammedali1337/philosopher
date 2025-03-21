#include "philo.h"

void des_free_all(char *str, t_table *table)
{
	int i;

	i = 0;
	if (str)
		write(2, str, ft_strlen(str));
	pthread_mutex_destroy(&table->output_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->death_lock);
	while (i < table->total_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	free(table->philo);
}

void    sleeping(t_philo *philo)
{
	ft_print("is sleeping", philo);
	ft_usleep(philo->table->sleep_duration);
}

void	thinking(t_philo *philo)
{
	ft_print("is thinking", philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print("had taken a fork", philo);
	if (philo->table->total_philos == 1)
	{
		ft_usleep(philo->table->death_time);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	ft_print("has take a fork", philo);
	philo->is_eating = 1;
	ft_print("is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_count++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->table->eat_duration);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}